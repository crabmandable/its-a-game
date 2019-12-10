#include "acolyte.hpp"

Acolyte::Acolyte() {
  mSheetName = "acolyte-sprites.png";
  mAnimations.insert({"idle", new Animation(2, 2, 28, 35, 30, 2)});
  mAnimations.insert({"walk", new Animation(2, 40, 31, 39, 15, 2)});
}
