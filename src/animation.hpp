#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL2/SDL.h>
class Animation {
  public:
    Animation(
        int x,
        int y,
        int width,
        int height,
        int frameLength,
        int nFrames,
        SDL_RendererFlip flip = SDL_FLIP_NONE
        );

      int x;
      int y;
      int width;
      int height;
      int frameLength;
      int nFrames;
      SDL_RendererFlip flip;
};
#endif // ANIMATION_H
