#include "room.hpp"
Room::Room() {
}

Room::~Room() {
}

void Room::drawForeground(Graphics& graphics, int elapsed_ms) {
  for (auto const obj: mForegroundObjects) {
    obj->draw(graphics, elapsed_ms);
  }
}
