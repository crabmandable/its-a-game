#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "animation.hpp"
class Sprite {
  public:
    void setSpriteSheet(std::string sheetName);
    void defineAnimation(std::string name, Animation* animation);
    void drawNextFrame(Graphics& graphics);
    void play(std::string animationName);
    void pause();

  protected:
    std::string mSheetName;
    int mGutterWidth = 2;
    std::map<std::string, Animation*> mAnimations;

  private:
    void getNextFrame(SDL_Rect& srcRect, SDL_RendererFlip& flip);

    int mFrameCounter = 0;
    bool mIsPlaying;
    std::string mCurrentAnimation;

    int mXPos = 0;
    int mYPos = 0;
};
#endif // SPRITE_H
