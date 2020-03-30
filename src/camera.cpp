#include "camera.hpp"
void Camera::updateTarget(Player& player, Room& room) {
  Position playerPos = player.getPosition();
  bool facingRight = player.getFacing();

  mTarget = playerPos;
  mTarget += kAhead * (facingRight > 0 ? 1 : -1);

  room.adjustCameraTarget(mTarget);

  // prevents camera going out of screen, which can happen when resizing
  room.adjustCameraTarget(mPosition);
}

void Camera::update(int elapsed_ms) {

  mVelocity = (mTarget - mPosition).absolute() * kDeccelerationFactor;
  mVelocity = Velocity::min(kMaxVelocity, mVelocity);
  mVelocity = Velocity::max(kMinVelocity, mVelocity);
  FloatPosition travelVector = mVelocity * elapsed_ms;

  if (mTarget.x < mPosition.x) {
    mPosition.x = std::max(mTarget.x, mPosition.x - travelVector.x);
  } else if (mTarget.x > mPosition.x) {
    mPosition.x = std::min(mTarget.x, mPosition.x + travelVector.x);
  }

  if (mTarget.y < mPosition.y) {
    mPosition.y = std::max(mTarget.y, mPosition.y - travelVector.y);
  } else if (mTarget.y > mPosition.y) {
    mPosition.y = std::min(mTarget.y, mPosition.y + travelVector.y);
  }
}

void Camera::updateViewPort(Graphics& graphics) {
  graphics.setViewPort(mPosition);
}

void Camera::setPosition(FloatPosition pos) {
  mPosition = pos;
}

FloatPosition Camera::getPosition() {
  return mPosition;
}
