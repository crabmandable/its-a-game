#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "sprite.hpp"
#include "graphics.hpp"
class GameObject {
  public:
    void draw(Graphics& graphics, int elapsed_ms);
    void setPos(int x, int y);
  protected:
    virtual Sprite* getSprite() = 0;
    int mXPos = 0;
    int mYPos = 0;
};
#endif
