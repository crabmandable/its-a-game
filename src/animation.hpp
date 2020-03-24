#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL2/SDL.h>
#include "geometry.hpp"
class Animation {
  public:
    static Animation* FlippedAnimation(Animation* animation, SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL);

    Animation();
    Animation(
        Rect rect,
        int nFrames = 1,
        int frameLength_ms = 100,
        SDL_RendererFlip flip = SDL_FLIP_NONE
        );

    Rect rect;
    int nFrames = 1;
    int frameLength = 100;
    int padding = 0;
    bool loop = true;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};
#endif // ANIMATION_H
