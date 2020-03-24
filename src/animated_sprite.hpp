#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "animation.hpp"
#include "sprite.hpp"
#include "geometry.hpp"

class AnimatedSprite : public Sprite {
  public:
    void defineAnimation(std::string name, Animation* animation);
    void drawNextFrame(Position pos, Graphics& graphics, int elapsed_ms);
    void play(std::string animationName);
    void pause();

  protected:
    std::map<std::string, Animation*> mAnimations;

  private:
    int mElapsed = 0;
    bool mIsPlaying;
    std::string mCurrentAnimation;
};
#endif // ANIMATED_SPRITE_H
