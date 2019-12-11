#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "sprite.hpp"
#include "graphics.hpp"
class GameObject {
  public:
    void draw(Graphics& graphics);
  private:
    int mXPos = 0;
    int mYPos = 0;
  protected:
    Sprite mSprite;
};
#endif
