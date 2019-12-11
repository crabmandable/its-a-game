#include "game.hpp"

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(SDL_DISABLE);

  mGraphics.init();

  gameLoop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::gameLoop() {
  int frameCounter = 0;

  while (mRunning) {
    frameCounter++;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    auto startTime = high_resolution_clock::now();

    handleInput();
    update();
    draw();

    auto elapsedLoopTime = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
    auto delay = milliseconds(1000/TARGET_FPS) - elapsedLoopTime;
    if (delay.count() > 0) {
      SDL_Delay(delay.count());
    }

    if (0 == frameCounter % 100) {
      auto frameDur = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
      printf("frame=%d, fps=%f\n", frameCounter, 1000.0 / frameDur.count());
    }
  }
}

void Game::update() {
  if (mInput.keyWasPressed(SDL_SCANCODE_D)) {
    mGameObject.walk(false);
  } else if (mInput.keyWasPressed(SDL_SCANCODE_A)) {
    mGameObject.walk(true);
  } else if (mInput.keyWasPressed(SDL_SCANCODE_S)) {
    mGameObject.idle();
  }
}

void Game::draw() {
  mGraphics.beginDraw();

  mGameObject.draw(mGraphics);
  
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

