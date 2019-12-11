#include "input.hpp"
void Input::beginFrame() {
  mPressedKeys.clear();
  mReleasedKeys.clear();
}

void Input::keyEvent(const SDL_KeyboardEvent& e) {
  if (e.type == SDL_KEYDOWN) {
    mPressedKeys[e.keysym.scancode] = true;
    mHeldKeys[e.keysym.scancode] = true;
  } else if (e.type == SDL_KEYUP) {
    mReleasedKeys[e.keysym.scancode] = false;
    mHeldKeys[e.keysym.scancode] = false;
  }
}

bool Input::keyWasPressed(SDL_Scancode key) {
  if (mPressedKeys.find(key) == mPressedKeys.end()) return false;
  else return mPressedKeys[key];
}

bool Input::keyIsHeld(SDL_Scancode key) {
  if (mHeldKeys.find(key) == mHeldKeys.end()) return false;
  else return mHeldKeys[key];
}

bool Input::keyWasReleased(SDL_Scancode key) {
  if (mReleasedKeys.find(key) == mReleasedKeys.end()) return false;
  else return mReleasedKeys[key];
}
