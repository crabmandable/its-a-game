#include "game_object.hpp"

void GameObject::draw(Graphics& graphics) {
  mSprite.drawNextFrame(mXPos, mYPos, graphics);
}

void GameObject::setPos(int x, int y) {
  mXPos = x;
  mYPos = y;
}
