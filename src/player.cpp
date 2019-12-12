#include "player.hpp"
Player::Player() {
  mSprite.setSpriteSheet("mario-sheet.png");
  mSprite.defineAnimation("idle_right", new Animation(80, 1, 15, 31));
  Animation* il = new Animation(80, 1, 15, 31);
  il->flip = SDL_FLIP_HORIZONTAL;
  mSprite.defineAnimation("idle_left", il);
  mSprite.defineAnimation("run_right", new Animation(97, 1, 15, 31, 3, 8));
  mSprite.defineAnimation("run_left", new Animation(97, 1, 15, 31, 3, 8, SDL_FLIP_HORIZONTAL));
  mSprite.defineAnimation("jump_right", new Animation(165, 1, 15, 31));
  Animation* jl = new Animation(165, 1, 15, 31);
  jl->flip = SDL_FLIP_HORIZONTAL;
  mSprite.defineAnimation("jump_left", jl);
}

void Player::update(Input& input) {
  updateState(input);
  updateXVelocity();
  updateYVelocity();
  updatePosition();
  updateAnimation();
}

void Player::updateState(Input& input) {
  bool right = input.keyIsHeld(SDL_SCANCODE_D);
  bool left = input.keyIsHeld(SDL_SCANCODE_A);
  bool jump = input.keyIsHeld(SDL_SCANCODE_SPACE) || input.keyIsHeld(SDL_SCANCODE_W);

  bool moving = false;
  if (right && !left) {
    mIsFacingRight = true;
    moving = true;
  } else if (left && !right) {
    mIsFacingRight = false;
    moving = true;
  }

  mState = State::Idle;
  if (jump) {
    mState = State::Jumping;
  } else if (moving) {
    mState = State::Running;
  }
}

void Player::updateXVelocity() {
  float dir = mIsFacingRight ? 1 : -1;

  if (mState == State::Running) {
    //increase the speeeeeed
    if (abs(mXVelocity) < kMaxSpeed) {
      mXVelocity = mXVelocity + (kAcceleration * dir);
      if (abs(mXVelocity) > kMaxSpeed) {
        mXVelocity = dir * kMaxSpeed;
      }
    }
  } else if (abs(mXVelocity) > 0) {
    float decel = mState == State::Jumping ? kJumpDeceleration : kDeceleration;
    mXVelocity = mXVelocity + ((-decel) * dir);
    if ((mIsFacingRight && mXVelocity < 0) || (!mIsFacingRight && mXVelocity > 0))
      mXVelocity = 0;
  }
}

void Player::updateYVelocity() {
  if (mState == State::Jumping) {
  }
}

void Player::updateAnimation() {
  switch(mState) {
    case State::Idle:
      if (mIsFacingRight) {
        mSprite.play("idle_right");
      } else {
        mSprite.play("idle_left");
      }
      break;
    case State::Running:
      if (mIsFacingRight) {
        mSprite.play("run_right");
      } else {
        mSprite.play("run_left");
      }
      break;
    case State::Jumping:
      if (mIsFacingRight) {
        mSprite.play("jump_right");
      } else {
        mSprite.play("jump_left");
      }
      break;
    default:
      break;
  };
}

void Player::updatePosition()
{
  mXPos += (int)mXVelocity;
}
