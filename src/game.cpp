#include "game.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(SDL_DISABLE);

  mGraphics.init();

  loadRoom("TestMap");

  gameLoop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::loadRoom(std::string name) {
  mRoom = new Room(name);

  // place player & camera in room
  FloatPosition start = mRoom->getStart();
  mPlayer.setPosition(start);
  mRoom->adjustCameraTarget(start);
  mCamera.setPosition(start);
  mPlayer.lockInput(100);
  mTransition.startTransition(Transition::Type::FadeIn, Transition::After::Disable);
}

void Game::gameLoop() {
  int frameCounter = 0;
  auto elapsed = high_resolution_clock::now();

  while (mRunning) {
    frameCounter++;
    auto startTime = high_resolution_clock::now();

    handleInput();
    int tick_ms = duration_cast<milliseconds>(high_resolution_clock::now() - elapsed).count();
    elapsed = high_resolution_clock::now();
#if DEBUG
    // need consistent tick for debugging
    tick_ms = 1000 / TARGET_FPS;
#endif
    update(tick_ms);
    draw(tick_ms);

    auto elapsedLoopTime = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
    auto delay = milliseconds(1000/TARGET_FPS) - elapsedLoopTime;
    if (delay.count() > 0) {
      SDL_Delay(delay.count());
    }

#if DEBUG
    if (0 == frameCounter % 100) {
      auto frameDur = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
      printf("frame=%d, fps=%f, delay=%ld\n", frameCounter, 1000.0 / frameDur.count(), delay.count());
    }
#endif
  }
}

void Game::update(int elapsed_ms) {
  mPlayer.update(mInput, elapsed_ms);
  updatePlayerPosition(elapsed_ms);

  mRoom->affectPlayer(mPlayer);

  mCamera.updateTarget(mPlayer, *mRoom);
  mCamera.update(elapsed_ms);
  mCamera.updateViewPort(mGraphics);

  mPlayer.updateAnimation();
  handlePlayerEvents();
}

void Game::draw(int elapsed_ms) {
  mGraphics.beginDraw();

  mRoom->drawTiles(mGraphics);
  mPlayer.draw(mGraphics, elapsed_ms);
  mTransition.updateAndDraw(mGraphics, elapsed_ms);
  mRoom->drawBackground(mGraphics);
  mGraphics.blitLayersToScreen();
  mRoom->drawOverlay(mGraphics);

#if DEBUG
  if (mShouldDrawCollision) {
    for (int i = 0; i < 4; i++) {
      using namespace Collision;
      CollisionEdge* playerEdge = mPlayer.getCollisionEdge(i);
      playerEdge->draw(mGraphics);
      std::vector<CollisionEdge*> tileEdges;
      mRoom->getCollisionEdgesNear(playerEdge->origin, playerEdge->orientation, tileEdges);
      for (auto edge: tileEdges) {
        edge->draw(mGraphics);
      }
    }

    for (auto edge : mCollidedEdges) {
      edge->draw(mGraphics, true);
    }
  }
#endif
  
  mGraphics.drawWindowBorders();
  mGraphics.present();
}

void Game::handleInput() {
  mInput.beginFrame();
  while(SDL_PollEvent(&mEvent)) {
    switch(mEvent.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        mInput.keyEvent(mEvent.key);
        break;
      case SDL_QUIT:
          mRunning = false;
        break;
      default: break;
    }
  }
}

void Game::updatePlayerPosition(int elapsed_ms) {
  using namespace Collision;

#if DEBUG
  for (auto edge: mCollidedEdges) delete edge;
  mCollidedEdges.clear();
#endif

  //handle player collisions
  bool colliding = false;
  bool grounded = false;
  do {
    colliding = false;
    for (int i = 0; i < 4; i++) {
      CollisionEdge* playerEdge = mPlayer.getCollisionEdge(i);

      std::vector<CollisionEdge*> tileEdges;
      mRoom->getCollisionEdgesNear(playerEdge->origin, playerEdge->orientation, tileEdges);

      for (auto edge: tileEdges) {
        Vector2D delta = detectCollision(*playerEdge, *edge, elapsed_ms);
        if (!delta.isZero()) {
          mPlayer.incrementPosition(-delta);

#ifdef DEBUG
          mCollidedEdges.push_back(new CollisionEdge(*edge));
          mCollidedEdges.push_back(new CollisionEdge(*playerEdge));
#endif

          colliding = true;
          break;
        }
      }

      for (auto edge: tileEdges) delete edge;

      if (colliding) {
        if (i == 3) {
          grounded = true;
        }
        break;
      }
    }
  } while (colliding);

  mPlayer.updatePosition(elapsed_ms);
  mPlayer.isGrounded(grounded);
}

void Game::handlePlayerEvents() {
  for (auto e: *mPlayer.getEvents()) {
    switch(e) {
      case Player::Event::Death: {
        Position origin = Position(SCREEN_WIDTH, SCREEN_HEIGHT) - ((Position(SCREEN_WIDTH, SCREEN_HEIGHT) / 2) + (Position)mCamera.getPosition() - mPlayer.getPosition());
        mTransition.startTransition(Transition::Type::Circle, Transition::After::Hold, origin);
        break;
      }
      case Player::Event::Respawn: {
        mTransition.startTransition(Transition::Type::FadeIn, Transition::After::Disable);
        FloatPosition cameraPos = mPlayer.getPosition();
        mRoom->adjustCameraTarget(cameraPos);
        mCamera.setPosition(cameraPos);
        break;
      }
      case Player::Event::InputLocked:
      case Player::Event::InputUnlocked:
        break;
    }
  }
}
