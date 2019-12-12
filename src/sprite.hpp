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
    void drawNextFrame(int x, int y, Graphics& graphics);
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
};
#endif // SPRITE_H
