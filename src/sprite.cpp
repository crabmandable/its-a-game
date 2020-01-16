#include "sprite.hpp"

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

Sprite::Sprite(std::string sheetName, int x, int y, int width, int height) {
  mSheetName = sheetName;
  mSpriteRect.x = x;
  mSpriteRect.y = y;
  mSpriteRect.w = width;
  mSpriteRect.h = height;
}

void Sprite::setSpriteSheet(std::string sheetName) {
  mSheetName = sheetName;
}

std::string Sprite::getSpriteSheet() {
  return mSheetName;
}

void Sprite::setSpriteLocation(SDL_Rect location) {
  mSpriteRect = location;
}

SDL_Rect Sprite::getSpriteLocation() {
  return mSpriteRect;
}

void Sprite::setFlip(SDL_RendererFlip flip) {
  mFlip = flip;
}

void Sprite::drawNextFrame(int x, int y, Graphics& graphics, int elapsed_ms) {
  (void) elapsed_ms;
  SDL_Rect dest;
  dest.w = mSpriteRect.w;
  dest.h = mSpriteRect.h;
  dest.x = x;
  dest.y = y;

  Graphics::DrawConfig config;
  config.flip = mFlip;
  graphics.drawTexture(mRenderLayer, mSheetName, mSpriteRect, dest, config);
}
