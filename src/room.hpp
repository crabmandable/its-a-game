#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "game_object.hpp"
#include "graphics.hpp"
class Room {
  public:
    Room();
    ~Room();
    void drawForeground(Graphics& graphics, int elapsed_ms);
  private:
    std::vector<GameObject*> mForegroundObjects;
};
#endif // ROOM_H
