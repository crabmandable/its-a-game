#include "acolyte.hpp"

Acolyte::Acolyte() {
  mSprite.setSpriteSheet("acolyte-sprites.png");
  mSprite.defineAnimation("idle", new Animation(2, 2, 28, 35, 30, 2));
  mSprite.defineAnimation("walk_right", new Animation(2, 40, 31, 39, 15, 2));
  mSprite.defineAnimation("walk_left", new Animation(2, 40, 31, 39, 15, 2, SDL_FLIP_HORIZONTAL));
  mSprite.play("idle");
}

void Acolyte::idle() {
  // std::cout << "imma stay a while" << std::endl;
  mSprite.play("idle");
}

void Acolyte::walk(bool left) {
  // std::cout << "imma head out" << std::endl;
  mSprite.play(left ? "walk_left" : "walk_right");
}
