#include "game.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(SDL_DISABLE);

  mGraphics.init();
  mRoom = new Room("TestMap.tmx");

  gameLoop();
}

Game::~Game() {
  SDL_Quit();
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
    update(tick_ms);
    draw(tick_ms);

    auto elapsedLoopTime = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
    auto delay = milliseconds(1000/TARGET_FPS) - elapsedLoopTime;
    if (delay.count() > 0) {
      SDL_Delay(delay.count());
    }

    if (0 == frameCounter % 100) {
      auto frameDur = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
      printf("frame=%d, fps=%f, delay=%ld\n", frameCounter, 1000.0 / frameDur.count(), delay.count());
    }
  }
}

void Game::update(int elapsed_ms) {
  mPlayer.update(mInput, elapsed_ms);
}

void Game::draw(int elapsed_ms) {
  mGraphics.beginDraw();

  mRoom->drawTiles(mGraphics, elapsed_ms);
  mPlayer.draw(mGraphics, elapsed_ms);
  
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

