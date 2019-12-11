#include "game_object.hpp"

void GameObject::draw(Graphics& graphics) {
  mSprite.drawNextFrame(graphics);
}
