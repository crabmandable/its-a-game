#ifndef _TRANSITION_HPP_
#define _TRANSITION_HPP_

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "graphics.hpp"

class Transition {
  public:
    enum class Type {
      Circle,
      FadeIn,
      BlackScreen
    };

    enum class After {
      Disable,
      Hold,
      Repeat
    };

    void updateAndDraw(Graphics& graphics, int elapsed_ms);
    void startTransition(Type type, After after, Position origin = Position());
  private:
    int getTransitionLength();

    bool mElapsing = false;
    bool mEnabled = false;
    int mElapsed_ms = 0;
    Type mType = Type::Circle;
    After mAfter = After::Hold;
    Position mOrigin;

    const std::map<Type, int> kTypeLengths{
      {Type::Circle, 600},
      {Type::FadeIn, 1000},
      {Type::BlackScreen, 1},
    };
};

#endif //_TRANSITION_HPP_
