#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL2/SDL.h>
class Animation {
  public:
    static Animation* FlippedAnimation(Animation* animation, SDL_RendererFlip flip);

    Animation();
    Animation(
        int x,
        int y,
        int width,
        int height,
        int nFrames = 1,
        int frameLength_ms = 100,
        SDL_RendererFlip flip = SDL_FLIP_NONE
        );

      int x = 0;
      int y = 0;
      int width = 0;
      int height = 0;
      int frameLength = 100;
      int nFrames = 1;
      bool loop = true;
      SDL_RendererFlip flip = SDL_FLIP_NONE;
};
#endif // ANIMATION_H
