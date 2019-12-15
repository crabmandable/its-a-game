#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.hpp"
class Sprite {
  public:
    void setSpriteSheet(std::string sheetName);
    void setSpriteLocation(SDL_Rect location);
    void setFlip(SDL_RendererFlip flip);
    virtual void drawNextFrame(int x, int y, Graphics& graphics, int elapsed_ms);
  protected:
    std::string mSheetName;
    SDL_RendererFlip mFlip = SDL_FLIP_NONE;

  private:
    SDL_Rect mSpriteRect;
};
#endif
