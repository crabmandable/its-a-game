#include "camera.hpp"
void Camera::updateTarget(Player& player, Room& room) {
  Position playerPos = player.getPosition();
  bool facingRight = player.getFacing();

  mTarget = playerPos;
  mTarget += kAhead * (facingRight > 0 ? 1 : -1);

  room.adjustCameraTarget(mTarget);
}

void Camera::update(int elapsed_ms) {

  mVelocity = Velocity::min(kMaxVelocity,  (Velocity)((mTarget - mPosition).absolute()) * kDeccelerationFactor);
  FloatPosition travelVector = FloatPosition::max(0.5f, mVelocity * elapsed_ms);
  FloatPosition floatPos = mPosition;
  FloatPosition target = mTarget;

  if (mTarget.x < mPosition.x) {
    mPosition.x = std::max(target.x, std::round(floatPos.x - travelVector.x));
  } else if (mTarget.x > mPosition.x) {
    mPosition.x = std::min(target.x, std::round(floatPos.x + travelVector.x));
  }

  if (mTarget.y < mPosition.y) {
    mPosition.y = std::max(target.y, std::round(floatPos.y - travelVector.y));
  } else if (mTarget.y > mPosition.y) {
    mPosition.y = std::min(target.y, std::round(floatPos.y + travelVector.y));
  }
}

void Camera::updateViewPort(Graphics& graphics) {
  graphics.setViewPort(mPosition);
}

void Camera::setPosition(Position pos) {
  mPosition = pos;
}
