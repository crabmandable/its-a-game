#include "camera.hpp"
void Camera::updateTarget(Player& player, Room& room) {
  player.getPosition(mTargetX, mTargetY);
  bool facingRight = player.getFacing();
  mTargetX += kXAhead * (facingRight > 0 ? 1 : -1);

  room.adjustCamera(mTargetX, mTargetY);
}

void Camera::update(int elapsed_ms) {
  mXVelocity = abs(mTargetX - mXPos) * kXDeccelerationFactor;
  mXVelocity = kMaxXVelocity < mXVelocity ? kMaxXVelocity : mXVelocity;

  if (mTargetX < mXPos) {
    mXPos = std::max(mTargetX, mXPos - (int)std::max(0.5f, (mXVelocity * elapsed_ms)));
  } else if (mTargetX > mXPos) {
    mXPos = std::min(mTargetX, mXPos + (int)std::max(0.5f, (mXVelocity * elapsed_ms)));
  }

  mYVelocity = abs(mTargetY - mYPos) * kYDeccelerationFactor;
  mYVelocity = kMaxYVelocity < mYVelocity ? kMaxYVelocity : mYVelocity;

  if (mTargetY < mYPos) {
    mYPos = std::max(mTargetY, mYPos - (int)std::max(0.5f, (mYVelocity * elapsed_ms)));
  } else if (mTargetY > mYPos) {
    mYPos = std::min(mTargetY, mYPos + (int)std::max(0.5f, (mYVelocity * elapsed_ms)));
  }
}

void Camera::updateViewPort(Graphics& graphics) {
  graphics.setViewPort(mXPos, mYPos);
}

void Camera::setPosition(int x, int y) {
  mXPos = x;
  mYPos = y;
}
