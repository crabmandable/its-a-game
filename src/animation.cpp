#include "animation.hpp"
Animation* Animation::FlippedAnimation(Animation* animation, SDL_RendererFlip flip) {
  auto a = new Animation(*animation);
  a->flip = (SDL_RendererFlip)(a->flip ^ flip);
  return a;
}

Animation::Animation() {
}

Animation::Animation(
    int x,
    int y,
    int width,
    int height,
    int nFrames,
    int frameLength,
    SDL_RendererFlip flip
    ) :
  x(x),
  y(y),
  width(width),
  height(height),
  nFrames(nFrames),
  frameLength(frameLength),
  flip(flip)
{};
