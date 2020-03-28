#include "player.hpp"
Player::Player() {
  mSprite.setSpriteSheet("KidSheet.png");

  auto idle = new Animation({{0, 0}, {24, 39}}, 4, 208);
  mSprite.defineAnimation("idle", idle);

  auto run =  new Animation({{0, 81}, {28, 42}}, 7, 80);
  mSprite.defineAnimation("run", run);

  Animation* jump = new Animation({{0, 39}, {28, 42}}, 2, 100);
  jump->loop = false;
  mSprite.defineAnimation("jump", jump);

  Animation* fall = new Animation({{112, 39}, {28, 40}}, 2, 180);
  mSprite.defineAnimation("fall", fall);

  Animation* fallMove = new Animation({{56, 39}, {28, 40}}, 2, 180);
  mSprite.defineAnimation("fall_move", fallMove);
}

void Player::update(Input& input, int elapsed_ms) {
  // clear events
  mEvents = std::vector<Event>();

  updateState(input, elapsed_ms);
  updateXVelocity(elapsed_ms);
  updateYVelocity(elapsed_ms);
  updateCollisionEdges();
}

std::vector<Player::Event>* Player::getEvents() {
  return &mEvents;
}

void Player::updateState(Input& input, int elapsed_ms) {
  if (mState == State::Dead) {
    mDeathElapsed += elapsed_ms;
    if (mDeathElapsed >= kRespawnTime_ms) {
      goToCheckpoint();
      mEvents.push_back(Event::Respawn);
      mState = State::Idle;
    }
    return;
  }

  bool left, right, jump = false;
  mDirection = 0;

  if (mInputLock_ms > 0) {
    mInputLock_ms -= elapsed_ms;
    if (mInputLock_ms <= 0) {
      mEvents.push_back(Event::InputUnlocked);
    }
  }

  if (mInputLock_ms <= 0) {
    right = input.keyIsHeld(SDL_SCANCODE_D);
    left = input.keyIsHeld(SDL_SCANCODE_A);
    jump = input.keyIsHeld(SDL_SCANCODE_SPACE) || input.keyIsHeld(SDL_SCANCODE_W);

    if (right && !left) {
      mIsFacingRight = true;
      mDirection = 1;
    } else if (left && !right) {
      mIsFacingRight = false;
      mDirection = -1;
    }
  }

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
  if (mState == State::Dead) return;
  //accelerate
  if (mDirection != 0) {
    mVelocity.x = mVelocity.x + (elapsed_ms * kAcceleration * (float)mDirection);

    // if we maxed out limit to max speed
    if ((mVelocity.x < 0 && mVelocity.x < -kMaxSpeed) ||
        (mVelocity.x > 0 && mVelocity.x > kMaxSpeed))
    {
      mVelocity.x = mDirection * kMaxSpeed;
    }
  }
  //decelerate
  else if (abs(mVelocity.x) > 0) {
    int dir = mIsFacingRight ? 1 : -1;

    float decel = mState == State::Jumping ? kJumpDeceleration : kDeceleration;
    mVelocity.x = mVelocity.x + (elapsed_ms * (-decel) * dir);
    if ((mIsFacingRight && mVelocity.x < 0) || (!mIsFacingRight && mVelocity.x > 0))
      mVelocity.x = 0;
  }
}

void Player::updateYVelocity(int elapsed_ms) {
  if (mState == State::Dead) return;
  if (mState == State::Jumping) {
    mVelocity.y = -kJumpForce;
  } else {
    mVelocity.y += kGravity * elapsed_ms;
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
      if (abs(mVelocity.x) < kMaxSpeed) {
        mSprite.play("fall");
      } else {
        mSprite.play("fall_move");
      }
      break;
    case State::Jumping:
      mSprite.play("jump");
      break;
    case State::Dead:
      if (mDeath == DeathType::Falling) {
        mSprite.setHidden(true);
      }
      break;
    default:
      break;
  };
}

void Player::updatePosition(int elapsed_ms)
{
  if (mState == State::Dead) return;

  // round x to make sure speed is equal in both directions
  // floor y to prevent jiggling up and down
  FloatPosition fp = ((FloatPosition)mPosition) + (mVelocity * elapsed_ms);
  mPosition = Position(std::round(fp.x), floor(fp.y));
}

Sprite* Player::getSprite() {
  return &mSprite;
}

Collision::CollisionEdge* Player::getCollisionEdge(int idx) {
  return mCollisionEdges + idx;
}

Position Player::getPosition() {
  return mPosition;
}

Velocity Player::getVelocity() {
  return mVelocity;
}

bool Player::getFacing() {
  return mIsFacingRight;
}

Player::State Player::getState() {
  return mState;
}

void Player::incrementPosition(Vector2D delta) {
  mPosition += delta;
  updateCollisionEdges();
}

void Player::setPosition(Position p) {
  mPosition = p;
  updateCollisionEdges();
}

void Player::updateCollisionEdges() {
  using namespace Collision;
  //left
  mCollisionEdges[0].origin = kCollisionOffset + mPosition;
  mCollisionEdges[0].origin.y -= kCollisionOverhang.x;
  mCollisionEdges[0].orientation = Orientation::X;
  mCollisionEdges[0].direction = CollisionDirection::Negative;
  mCollisionEdges[0].length = kCollisionLength.x + kCollisionOverhang.x;
  mCollisionEdges[0].velocity = mVelocity;

  //top
  mCollisionEdges[1].origin = kCollisionOffset + mPosition;
  mCollisionEdges[1].origin.x -= kCollisionOverhang.y;
  mCollisionEdges[1].orientation = Orientation::Y;
  mCollisionEdges[1].direction = CollisionDirection::Negative;
  mCollisionEdges[1].length = kCollisionLength.y + (kCollisionOverhang.y * 2);
  mCollisionEdges[1].velocity = mVelocity;

  //right
  mCollisionEdges[2].origin = kCollisionOffset + mPosition;
  mCollisionEdges[2].origin.x += kCollisionLength.y;
  mCollisionEdges[2].origin.y -= kCollisionOverhang.y;
  mCollisionEdges[2].orientation = Orientation::X;
  mCollisionEdges[2].direction = CollisionDirection::Positive;
  mCollisionEdges[2].length = kCollisionLength.x + kCollisionOverhang.x;
  mCollisionEdges[2].velocity = mVelocity;

  //bottom
  mCollisionEdges[3].origin = kCollisionOffset + mPosition;
  mCollisionEdges[3].origin.x -= kCollisionOverhang.y;
  mCollisionEdges[3].origin.y += kCollisionLength.x;
  mCollisionEdges[3].orientation = Orientation::Y;
  mCollisionEdges[3].direction = CollisionDirection::Positive;
  mCollisionEdges[3].length = kCollisionLength.y + (kCollisionOverhang.y * 2);
  mCollisionEdges[3].velocity = mVelocity;
}

void Player::isGrounded(bool grounded) {
  mGrounded = grounded;
  if (grounded) {
    mState = mDirection != 0 ? State::Running : State::Idle;
    mVelocity.y = 0;
    for (int i = 0; i < 4; i++) {
      mCollisionEdges[i].velocity.y = 0;
    }
  }
}

void Player::setCheckpoint(Checkpoint* checkpoint) {
  mCheckpoint = checkpoint;
}

void Player::goToCheckpoint() {
  if (!mCheckpoint) return;

  setPosition(mCheckpoint->getSpawn());
}

void Player::killPlayer(DeathType t) {
  if (mState == State::Dead) return;

  mDeath = t;
  mState = State::Dead;
  mDeathElapsed = 0;
  mVelocity = Velocity(0, 0);
  mEvents.push_back(Event::Death);
  lockInput(500);
}

void Player::lockInput(int time_ms) {
  mInputLock_ms = time_ms;
  mEvents.push_back(Event::InputLocked);
}
