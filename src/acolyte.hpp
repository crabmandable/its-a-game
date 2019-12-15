#ifndef ACOLYTE_H
#define ACOLYTE_H
#include "game_object.hpp"
#include <iostream>
#include "animated_sprite.hpp"

class Acolyte : public GameObject {
  public:
    Acolyte();
    void walk(bool left);
    void idle();
  protected:
    Sprite* getSprite();
  private:
    AnimatedSprite mSprite;
};
#endif // ACOLYTE_H
