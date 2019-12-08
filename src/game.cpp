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
}

void Game::draw() {
  mGraphics.beginDraw();

  SDL_Rect srcR;
  srcR.w = 640;
  srcR.h = 360;
  srcR.x = 0;
  srcR.y = (480 - 360) / 2;

  SDL_Rect destR;
  destR.w = 640;
  destR.h = 360;

  mGraphics.drawTexture("town.bmp", srcR, destR);

  srcR.w = 64;
  srcR.h = 64;
  destR.w = 64;
  destR.h = 64;
  mGraphics.drawTexture("town.png", srcR, destR);
  
  mGraphics.present();
}

void Game::handleInput() {
  while(SDL_PollEvent(&mEvent)) {
    switch(mEvent.type) {
      case SDL_KEYDOWN:
        if (mEvent.key.keysym.sym == SDLK_ESCAPE) {
          mRunning = false;
        }
        break;
      case SDL_QUIT:
          mRunning = false;
        break;
      default: break;
    }
  }
}

