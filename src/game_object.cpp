#include "game_object.hpp"

void GameObject::draw(Graphics& graphics, int elapsed_ms) {
  getSprite()->drawNextFrame(mXPos, mYPos, graphics, elapsed_ms);
}

void GameObject::setPos(int x, int y) {
  mXPos = x;
  mYPos = y;
}
