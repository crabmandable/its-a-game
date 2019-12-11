#include "animation.hpp"
Animation::Animation(
    int x,
    int y,
    int width,
    int height,
    int frameLength,
    int nFrames,
    SDL_RendererFlip flip
    ) :
  x(x),
  y(y),
  width(width),
  height(height),
  frameLength(frameLength),
  nFrames(nFrames),
  flip(flip)
{};
