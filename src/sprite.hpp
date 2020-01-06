#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.hpp"
class Sprite {
  public:
    Sprite();
    ~Sprite();
    Sprite(std::string sheetName, int x, int y, int width, int height);
    void setSpriteSheet(std::string sheetName);
    std::string getSpriteSheet();
    void setSpriteLocation(SDL_Rect location);
    SDL_Rect getSpriteLocation();
    void setFlip(SDL_RendererFlip flip);
    virtual void drawNextFrame(int x, int y, Graphics& graphics, int elapsed_ms);
  protected:
    std::string mSheetName;
    SDL_RendererFlip mFlip = SDL_FLIP_NONE;
    Graphics::RenderLayer mRenderLayer = Graphics::RenderLayer::Foreground;

  private:
    SDL_Rect mSpriteRect;
};
#endif
