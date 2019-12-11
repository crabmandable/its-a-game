#include "sprite.hpp"
void Sprite::play(std::string animationName) {
  if (animationName == mCurrentAnimation && mIsPlaying) {
    return;
  }

  if (mAnimations.find(animationName) == mAnimations.end()) {
    std::cout << "Unable to find animation: " << animationName;
    return;
  }

  mCurrentAnimation = animationName;
  mFrameCounter = 0;
  mIsPlaying = true;
}

void Sprite::pause() {
  mIsPlaying = false;
}

void Sprite::getNextFrame(SDL_Rect& srcRect, SDL_RendererFlip& flip) {
  Animation* anim = mAnimations[mCurrentAnimation];
  flip = anim->flip;

  srcRect.w = anim->width;
  srcRect.h = anim->height;
  srcRect.y = anim->y;

  int animLength = anim->frameLength * anim->nFrames;
  int frame = floor(((float)(mFrameCounter % animLength)) / anim->frameLength);
  srcRect.x = frame * (anim->width + mGutterWidth) + anim->x;

  if (mIsPlaying) {
    mFrameCounter++;
  }
}

void Sprite::drawNextFrame(Graphics& graphics)
{
  SDL_RendererFlip flip;
  SDL_Rect src;
  getNextFrame(src, flip);

  SDL_Rect dest;
  dest.w = src.w;
  dest.h = src.h;
  dest.x = mXPos;
  dest.y = mYPos;

  graphics.drawTexture(mSheetName, src, dest, flip);
}

void Sprite::setSpriteSheet(std::string sheetName) {
  mSheetName = sheetName;
}

void Sprite::defineAnimation(std::string name, Animation* animation)
{
  mAnimations.insert({name, animation});
}
