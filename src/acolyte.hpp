#ifndef ACOLYTE_H
#define ACOLYTE_H
#include "game_object.hpp"
#include <iostream>

class Acolyte : public GameObject {
  public:
    Acolyte();
    void walk();
    void idle();
};
#endif // ACOLYTE_H
