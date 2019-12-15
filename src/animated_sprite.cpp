#include "animated_sprite.hpp"
void AnimatedSprite::play(std::string animationName) {
  if (animationName == mCurrentAnimation && mIsPlaying) {
    return;
  }

  if (mAnimations.find(animationName) == mAnimations.end()) {
    std::cout << "Unable to find animation: " << animationName;
    return;
  }

  mCurrentAnimation = animationName;
  mElapsed = 0;
  mIsPlaying = true;
}

void AnimatedSprite::pause() {
  mIsPlaying = false;
}

void AnimatedSprite::drawNextFrame(int x, int y, Graphics& graphics, int elapsed_ms)
{
  if (mIsPlaying) {
    mElapsed += elapsed_ms;
  }

  Animation* anim = mAnimations[mCurrentAnimation];

  SDL_Rect src;
  src.w = anim->width;
  src.h = anim->height;
  src.y = anim->y;

  if (anim->frameLength < 2) {
    src.x = anim->x;
  } else {
    int animLength = anim->frameLength * anim->nFrames;
    int frame = floor(((float)(mElapsed % animLength)) / anim->frameLength);
    src.x = frame * (anim->width + mGutterWidth) + anim->x;
  }

  SDL_Rect dest;
  dest.w = src.w;
  dest.h = src.h;
  dest.x = x;
  dest.y = y;

  graphics.drawTexture(mSheetName, src, dest, (SDL_RendererFlip)(anim->flip ^ mFlip));
}

void AnimatedSprite::defineAnimation(std::string name, Animation* animation)
{
  mAnimations.insert({name, animation});
}
