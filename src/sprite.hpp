#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.hpp"
#include "geometry.hpp"
class Sprite {
  public:
    Sprite();
    ~Sprite();
    Sprite(std::string sheetName, Rect r);
    void setSpriteSheet(std::string sheetName);
    std::string getSpriteSheet();
    void setSpriteLocation(SDL_Rect location);
    void setSpriteLocation(Rect location);
    Rect getSpriteLocation();
    void setFlip(SDL_RendererFlip flip);
    void setHidden(bool hidden);
    virtual void drawNextFrame(Position position, Graphics& graphics, int elapsed_ms);
  protected:
    bool mHidden = false;
    std::string mSheetName;
    SDL_RendererFlip mFlip = SDL_FLIP_NONE;
    Graphics::RenderLayer mRenderLayer = Graphics::RenderLayer::Foreground;

  private:
    Rect mSpriteRect;
};
#endif
