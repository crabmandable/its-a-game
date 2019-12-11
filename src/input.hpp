#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include <map>
#include <iostream>
class Input {
  public:
    void beginFrame();
    void keyEvent(const SDL_KeyboardEvent& e);
    bool keyWasPressed(SDL_Scancode key);
    bool keyIsHeld(SDL_Scancode key);
    bool keyWasReleased(SDL_Scancode key);

  private:
    std::map<SDL_Scancode, bool> mHeldKeys;
    std::map<SDL_Scancode, bool> mPressedKeys;
    std::map<SDL_Scancode, bool> mReleasedKeys;
};
#endif // INPUT_H
