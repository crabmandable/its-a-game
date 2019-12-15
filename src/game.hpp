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
#include "input.hpp"
#include "player.hpp"

class Game {
  public:
    static const int TARGET_FPS = 60;

    Game();
    ~Game();

  private:
    void gameLoop();
    void update(int elapsed_ms);
    void draw();
    void handleInput();

    SDL_Event mEvent;
    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    bool mRunning{true};

    Graphics mGraphics;
    Input mInput;
    Player mPlayer;
};

#endif //GAME_H_
