#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL2/SDL.h>
class Animation {
  public:
    Animation();
    Animation(
        int x,
        int y,
        int width,
        int height,
        int nFrames = 1,
        int frameLength = 60,
        SDL_RendererFlip flip = SDL_FLIP_NONE
        );

      int x = 0;
      int y = 0;
      int width = 0;
      int height = 0;
      int frameLength = 60;
      int nFrames = 1;
      SDL_RendererFlip flip = SDL_FLIP_NONE;
};
#endif // ANIMATION_H
