#ifndef GAME_H_
#define GAME_H_
#include <chrono>
#include <algorithm>
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>
#include "asset.hpp"
#include "graphics.hpp"
#include "acolyte.hpp"

class Game {
  public:
    static const int TARGET_FPS = 60;

    Game();
    ~Game();

  private:
    void gameLoop();
    void update();
    void draw();
    void handleInput();

    SDL_Event mEvent;
    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    bool mRunning{true};

    Graphics mGraphics;
    Acolyte mSprite;
};

#endif //GAME_H_
