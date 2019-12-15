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
class AnimatedSprite : public Sprite {
  public:
    void defineAnimation(std::string name, Animation* animation);
    void drawNextFrame(int x, int y, Graphics& graphics, int elapsed_ms);
    void play(std::string animationName);
    void pause();

  protected:
    int mGutterWidth = 2;
    std::map<std::string, Animation*> mAnimations;

  private:
    int mElapsed = 0;
    bool mIsPlaying;
    std::string mCurrentAnimation;
};
#endif // ANIMATED_SPRITE_H
