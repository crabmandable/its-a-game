#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "sprite.hpp"
#include "graphics.hpp"
class GameObject {
  public:
    void draw(Graphics& graphics);
    void setPos(int x, int y);
  protected:
    Sprite mSprite;
    int mXPos = 0;
    int mYPos = 0;
};
#endif
