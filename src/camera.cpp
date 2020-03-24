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

  if (mTarget.x < mPosition.x) {
    mPosition.x = std::max(mTarget.x, std::round(mPosition.x - travelVector.x));
  } else if (mTarget.x > mPosition.x) {
    mPosition.x = std::min(mTarget.x, std::round(mPosition.x + travelVector.x));
  }

  if (mTarget.y < mPosition.y) {
    mPosition.y = std::max(mTarget.y, std::round(mPosition.y - travelVector.y));
  } else if (mTarget.y > mPosition.y) {
    mPosition.y = std::min(mTarget.y, std::round(mPosition.y + travelVector.y));
  }
}

void Camera::updateViewPort(Graphics& graphics) {
  graphics.setViewPort(mPosition);
}

void Camera::setPosition(Position pos) {
  mPosition = pos;
}
