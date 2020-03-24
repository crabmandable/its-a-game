#include "sprite.hpp"

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

Sprite::Sprite(std::string sheetName, Rect r) {
  mSheetName = sheetName;
  mSpriteRect = r;
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

void Sprite::setSpriteLocation(Rect location) {
  mSpriteRect = location;
}

Rect Sprite::getSpriteLocation() {
  return mSpriteRect;
}

void Sprite::setFlip(SDL_RendererFlip flip) {
  mFlip = flip;
}

void Sprite::drawNextFrame(Position p, Graphics& graphics, int elapsed_ms) {
  (void) elapsed_ms;

  Rect dest, src = mSpriteRect; 

  dest.origin = p;

  Graphics::DrawConfig config;
  config.flip = mFlip;
  graphics.drawTexture(mRenderLayer, mSheetName, src, dest, config);
}
