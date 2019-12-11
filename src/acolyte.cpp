#include "acolyte.hpp"

Acolyte::Acolyte() {
  mSprite.setSpriteSheet("acolyte-sprites.png");
  mSprite.defineAnimation("idle", new Sprite::Animation(2, 2, 28, 35, 30, 2));
  mSprite.defineAnimation("walk", new Sprite::Animation(2, 40, 31, 39, 15, 2));
  mSprite.play("idle");
}

void Acolyte::idle() {
  // std::cout << "imma stay a while" << std::endl;
  mSprite.play("idle");
}

void Acolyte::walk() {
  // std::cout << "imma head out" << std::endl;
  mSprite.play("walk");
}
