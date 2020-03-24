#include "game_object.hpp"

void GameObject::draw(Graphics& graphics, int elapsed_ms) {
  getSprite()->drawNextFrame(mPosition, graphics, elapsed_ms);
}

void GameObject::setPosition(Position p) {
  mPosition = p;
}
