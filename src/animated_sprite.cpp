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

void AnimatedSprite::drawNextFrame(Position pos, Graphics& graphics, int elapsed_ms)
{
  if (mIsPlaying) {
    mElapsed += elapsed_ms;
  }

  Animation* anim = mAnimations[mCurrentAnimation];

  Rect src = anim->rect;

  if (anim->frameLength >= 2) {
    int animLength = anim->frameLength * anim->nFrames;
    int frame;
    if (anim->loop) {
      frame = floor(((float)(mElapsed % animLength)) / anim->frameLength);
    } else {
      frame = std::min(anim->frameLength, (int)(((float)(mElapsed / animLength)) / anim->frameLength));
    }
    src.origin.x = frame * (src.size.w + anim->padding) + src.origin.x;
  }

  Rect dest = src;
  dest.origin = pos;

  Graphics::DrawConfig config;
  config.flip = (SDL_RendererFlip)(anim->flip ^ mFlip);
  graphics.drawTexture(mRenderLayer, mSheetName, src, dest, config);
}

void AnimatedSprite::defineAnimation(std::string name, Animation* animation)
{
  mAnimations.insert({name, animation});
}
