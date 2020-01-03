#include "player.hpp"
Player::Player() {
  mSprite.setSpriteSheet("KidSheet.png");

  auto idle = new Animation(0, 0, 24, 37, 1/*4*/, 180);
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
  updateCollisionEdges();
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

  // mGrounded = mYPos >= (32 * 9) - 37; // TODO get real collision
  
  if (mGrounded) {
    if (jump) {
      mState = State::Jumping;
      mJumpElapsed = 0;
      mGrounded = false;
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
    mYVelocity = -kJumpForce;
  } else {
    mYVelocity += kGravity * elapsed_ms;
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
  mYPos += (int)(mYVelocity * elapsed_ms);
  
  //todo hard coded screen size
  if (mXPos < -4 || mXPos > 640) {
    mXPos = 0;
    mGrounded = false;
    mXVelocity = 0;
  }
  if (mYPos < -4 || mYPos > 360) {
    mYPos = 0;
    mGrounded = false;
    mYVelocity = 0;
  }
}

Sprite* Player::getSprite() {
  return &mSprite;
}

Collision::CollisionEdge* Player::getCollisionEdge(int idx) {
  return mCollisionEdges + idx;
}

void Player::getPosition(int &x, int &y) {
  x = mXPos;
  y = mYPos;
}

void Player::incrementPosition(int x, int y) {
  mXPos += x;
  mYPos += y;
  updateCollisionEdges();
}

void Player::updateCollisionEdges() {
  using namespace Collision;
  //left
  mCollisionEdges[0].originX = kCollisionXOffset + mXPos;
  mCollisionEdges[0].originY = kCollisionYOffset + mYPos;
  mCollisionEdges[0].orientation = Orientation::X;
  mCollisionEdges[0].direction = CollisionDirection::Negative;
  mCollisionEdges[0].length = kCollisionXLength;
  mCollisionEdges[0].velocityX = mXVelocity;
  mCollisionEdges[0].velocityY = mYVelocity;

  //top
  mCollisionEdges[1].originX = kCollisionXOffset + mXPos;
  mCollisionEdges[1].originY = kCollisionYOffset + mYPos;
  mCollisionEdges[1].orientation = Orientation::Y;
  mCollisionEdges[1].direction = CollisionDirection::Negative;
  mCollisionEdges[1].length = kCollisionYLength;
  mCollisionEdges[1].velocityX = mXVelocity;
  mCollisionEdges[1].velocityY = mYVelocity;

  //right
  mCollisionEdges[2].originX = kCollisionXOffset + mXPos + kCollisionYLength;
  mCollisionEdges[2].originY = kCollisionYOffset + mYPos;
  mCollisionEdges[2].orientation = Orientation::X;
  mCollisionEdges[2].direction = CollisionDirection::Positive;
  mCollisionEdges[2].length = kCollisionXLength;
  mCollisionEdges[2].velocityX = mXVelocity;
  mCollisionEdges[2].velocityY = mYVelocity;

  //bottom
  mCollisionEdges[3].originX = kCollisionXOffset + mXPos;
  mCollisionEdges[3].originY = kCollisionYOffset + mYPos + kCollisionXLength;
  mCollisionEdges[3].orientation = Orientation::Y;
  mCollisionEdges[3].direction = CollisionDirection::Positive;
  mCollisionEdges[3].length = kCollisionYLength;
  mCollisionEdges[3].velocityX = mXVelocity;
  mCollisionEdges[3].velocityY = mYVelocity;
}

void Player::isGrounded(bool grounded) {
  mGrounded = grounded;
  if (grounded) {
    mState = mDirection != 0 ? State::Running : State::Idle;
    mYVelocity = 0;
    for (int i = 0; i < 4; i++) {
      mCollisionEdges[i].velocityY = 0;
    }
  }
}

