#ifndef ACOLYTE_H
#define ACOLYTE_H
#include "game_object.hpp"
#include <iostream>

class Acolyte : public GameObject {
  public:
    Acolyte();
    void walk(bool left);
    void idle();
};
#endif // ACOLYTE_H
