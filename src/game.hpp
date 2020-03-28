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
#include "camera.hpp"
#include "transition.hpp"
#include "geometry.hpp"

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
    void loadRoom(std::string name);
    void update(int elapsed_ms);
    void draw(int elapsed_ms);
    void handleInput();
    void updatePlayerPosition(int elapsed_ms);
    void handlePlayerEvents();

    SDL_Event mEvent;
    bool mRunning{true};

#if DEBUG
    bool mShouldDrawCollision = true;
#endif

    Graphics mGraphics;
    Input mInput;
    Transition mTransition;
    Player mPlayer;
    Camera mCamera;
    Room* mRoom;

#ifdef DEBUG
    std::vector<Collision::CollisionEdge*> mCollidedEdges{std::vector<Collision::CollisionEdge*>()};
#endif
};

#endif //GAME_H_
