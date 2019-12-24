#include "player.hpp"
Player::Player() {
  mSprite.setSpriteSheet("KidSheet.png");

  auto idle = new Animation(0, 0, 24, 37, 4, 180);
  mSprite.defineAnimation("idle", idle);

  auto run =  new Animation(0, 37, 28, 40, 7, 128);
  mSprite.defineAnimation("run", run);

  Animation* jump = new Animation(0, 77, 28, 40, 2, 100);
  jump->loop = false;
  mSprite.defineAnimation("jump", jump);

  Animation* fall = new Animation(112, 77, 28, 40, 2, 180);
  mSprite.defineAnimation("fall", fall);

  Animation* fallMove = new Animation(56, 77, 28, 40, 2, 180);
  mSprite.defineAnimation("fall_move", fallMove);
}

void Player::update(Input& input, int elapsed_ms) {
  updateState(input, elapsed_ms);
  updateXVelocity(elapsed_ms);
  updateYVelocity(elapsed_ms);
  updatePosition(elapsed_ms);
  updateAnimation();
}

void Player::updateState(Input& input, int elapsed_ms) {
  bool right = input.keyIsHeld(SDL_SCANCODE_D);
  bool left = input.keyIsHeld(SDL_SCANCODE_A);
  bool jump = input.keyIsHeld(SDL_SCANCODE_SPACE) || input.keyIsHeld(SDL_SCANCODE_W);

  mDirection = 0;
  if (right && !left) {
    mIsFacingRight = true;
    mDirection = 1;
  } else if (left && !right) {
    mIsFacingRight = false;
    mDirection = -1;
  }

  mGrounded = mYPos >= (32 * 9) - 37; // TODO get real collision
  
  if (mGrounded) {
    if (jump) {
      mState = State::Jumping;
      mJumpElapsed = 0;
    } else if (mDirection != 0) {
      mState = State::Running;
    } else {
      mState = State::Idle;
    }
  } else {
    if (mState == State::Jumping && jump) {
      mJumpElapsed += elapsed_ms;
      if (mJumpElapsed >= kJumpLength_ms) {
        mState = State::Falling;
      }
    } else {
      mState = State::Falling;
    }
  }
}

void Player::updateXVelocity(int elapsed_ms) {
  //accelerate
  if (mDirection != 0) {
    //if we didnt max out
    if ((mDirection > 0 && mXVelocity < kMaxSpeed) || (mDirection < 0 && mXVelocity > -kMaxSpeed))
    {
      mXVelocity += elapsed_ms * kAcceleration * mDirection;
    }
    //if we did max out
    else if ((mXVelocity < 0 && mXVelocity < -kMaxSpeed) ||
        (mXVelocity > 0 && mXVelocity > kMaxSpeed))
    {
      mXVelocity = mDirection * kMaxSpeed;
    }
  }
  //decelerate
  else if (abs(mXVelocity) > 0) {
    int dir = mIsFacingRight ? 1 : -1;

    float decel = mState == State::Jumping ? kJumpDeceleration : kDeceleration;
    mXVelocity = mXVelocity + (elapsed_ms * (-decel) * dir);
    if ((mIsFacingRight && mXVelocity < 0) || (!mIsFacingRight && mXVelocity > 0))
      mXVelocity = 0;
  }

  // if (abs(mXVelocity) > 0) {
  //   printf("vel:%f, dir:%d, mDir:%d\n", mXVelocity, dir, mDirection);
  // }
}

void Player::updateYVelocity(int elapsed_ms) {
  if (mState == State::Jumping) {
    mYVelocity = kJumpForce;
  } else if (mGrounded) {
    mYVelocity = 0;
  } else if (mState == State::Falling) {
    mYVelocity -= kGravity * elapsed_ms;
  }
}

void Player::updateAnimation() {
  if (mIsFacingRight) {
    mSprite.setFlip(SDL_FLIP_NONE);
  } else {
    mSprite.setFlip(SDL_FLIP_HORIZONTAL);
  }

  switch(mState) {
    case State::Idle:
      mSprite.play("idle");
      break;
    case State::Running:
      mSprite.play("run");
      break;
    case State::Falling:
      if (abs(mXVelocity) < kMaxSpeed) {
        mSprite.play("fall");
      } else {
        mSprite.play("fall_move");
      }
      break;
    case State::Jumping:
      mSprite.play("jump");
      break;
    default:
      break;
  };
}

void Player::updatePosition(int elapsed_ms)
{
  mXPos += (int)(mXVelocity * elapsed_ms);
  mYPos -= (int)(mYVelocity * elapsed_ms);
}

Sprite* Player::getSprite() {
  return &mSprite;
}
