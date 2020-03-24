#include "animation.hpp"
Animation* Animation::FlippedAnimation(Animation* animation, SDL_RendererFlip flip) {
  auto a = new Animation(*animation);
  a->flip = (SDL_RendererFlip)(a->flip ^ flip);
  return a;
}

Animation::Animation() {
}

Animation::Animation(
    Rect rect,
    int nFrames,
    int frameLength,
    SDL_RendererFlip flip
    ) :
  rect(rect),
  nFrames(nFrames),
  frameLength(frameLength),
  flip(flip)
{}
