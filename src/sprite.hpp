#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"
class Sprite {
  public:
    void drawNextFrame(Graphics& graphics);
    void play(std::string animationName);
    void pause();

  protected:
    struct Animation {
      int x;
      int y;
      int width;
      int height;
      int frameLength;
      int nFrames;

      Animation(
          int x,
          int y,
          int width,
          int height,
          int frameLength,
          int nFrames
          ) :
        x(x),
        y(y),
        width(width),
        height(height),
        frameLength(frameLength),
        nFrames(nFrames)
      {};
    };
    std::string mSheetName;
    int mGutterWidth = 2;
    std::map<std::string, Animation*> mAnimations;

  private:
    void getNextFrame(SDL_Rect& srcRect);

    int mFrameCounter = 0;
    bool mIsPlaying;
    std::string mCurrentAnimation;

    int mXPos = 0;
    int mYPos = 0;
};
#endif // SPRITE_H
