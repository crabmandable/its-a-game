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
#include "room.hpp"

#ifndef DEBUG
#define DEBUG false
#endif
class Game {
  public:
    static const int TARGET_FPS = 60;

    Game();
    ~Game();

  private:
    void gameLoop();
    void update(int elapsed_ms);
    void draw(int elapsed_ms);
    void handleInput();
    void updatePlayerPosition(int elapsed_ms);

    SDL_Event mEvent;
    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    bool mRunning{true};

    bool mShouldDrawCollision = DEBUG;

    Graphics mGraphics;
    Input mInput;
    Player mPlayer;
    Room* mRoom;

#ifdef DEBUG
    std::vector<Collision::CollisionEdge*> mCollidedEdges{std::vector<Collision::CollisionEdge*>()};
#endif
};

#endif //GAME_H_
