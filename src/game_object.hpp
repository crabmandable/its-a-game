#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "sprite.hpp"
#include "graphics.hpp"
#include "geometry.hpp"
class GameObject {
  public:
    void draw(Graphics& graphics, int elapsed_ms);
    void setPosition(Position pos);
  protected:
    virtual Sprite* getSprite() = 0;
    Position mPosition;
};
#endif
