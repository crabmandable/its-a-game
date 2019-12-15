#include "game.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

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
  auto gameStartTime = high_resolution_clock::now();
  auto elapsed = high_resolution_clock::now();

  while (mRunning) {
    frameCounter++;
    auto startTime = high_resolution_clock::now();

    handleInput();
    int tick_ms = duration_cast<milliseconds>(high_resolution_clock::now() - elapsed).count();
    elapsed = high_resolution_clock::now();
    update(tick_ms);
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

void Game::update(int elapsed_ms) {
  mPlayer.update(mInput, elapsed_ms);
}

void Game::draw() {
  mGraphics.beginDraw();

  mPlayer.draw(mGraphics);
  
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

