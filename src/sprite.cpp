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

void Sprite::setSpriteLocation(SDL_Rect location) {
  mSpriteRect = location;
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
  graphics.drawTexture(mSheetName, mSpriteRect, dest, mFlip);
}
