#include "transition.hpp"

void Transition::updateAndDraw(Graphics& graphics, int elapsed_ms) {
  if (!mEnabled) return;

  graphics.setTransitionAlphaMod(0xFF);

  if (mElapsing) {
    mElapsed_ms += elapsed_ms;
  }

  if (mElapsing && mElapsed_ms >= kTypeLengths.at(mType)) {
    switch(mAfter) {
      case After::Repeat:
        mElapsed_ms = 0;
        break;
      case After::Disable:
        graphics.setTransitionAlphaMod(0);
        mEnabled = false;
        return;
      case After::Hold:
        mElapsing = false;
        break;
      default:
        std::cout << "Error: Unhanlded 'After' transition" << std::endl;
        break;
    }
  }

  SDL_Renderer* renderer = graphics.getRenderer(Graphics::RenderLayer::Transition);
  SDL_Rect rect;
  rect.x = rect.y = 0;
  rect.w = Graphics::SCREEN_WIDTH;
  rect.h = Graphics::SCREEN_HEIGHT;

  if (mType == Type::Circle) {
    // first overlay everything with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    //now punch a whole through the middle with white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    int transitionLength = getTransitionLength();
    float radiusFactor = (float)(transitionLength - mElapsed_ms) / transitionLength;
    int radius = Graphics::SCREEN_WIDTH * radiusFactor;
    filledCircleColor(
        renderer,
        mOrigin.x,
        mOrigin.y,
        radius,
        0xFFFFFFFF
    );
  } else if (mType == Type::FadeIn) {
    int fadeLength = getTransitionLength();
    int alphaMod = 0xFF * ((float)fadeLength - mElapsed_ms) / (fadeLength - 200);
    graphics.setTransitionAlphaMod(std::min(alphaMod, 0xFF));
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
  } else if (mType == Type::BlackScreen) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
  }
}

void Transition::startTransition(Type type, After after, Position origin) {
  mType = type;
  mAfter = after;
  mElapsing = true;
  mEnabled = true;
  mElapsed_ms = 0;
  mOrigin = origin;
  mOrigin = Position::max(mOrigin, {0, 0});
  mOrigin = Position::min(mOrigin, {Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT});
}

int Transition::getTransitionLength() {
  return kTypeLengths.at(mType);
}
