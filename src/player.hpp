#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <algorithm>
class Player : public GameObject {
  public:
    const float kAcceleration = 0.6;
    const float kDeceleration = 1;
    const float kJumpDeceleration = 0.03;
    const float kMaxSpeed = 5;
    const float kJumpForce = 2;
    const float kGravity = 0.98;

    enum class State {
      Idle,
      Running,
      Jumping
    };

    Player();
    void update(Input& input);
    void updateXVelocity();
    void updateYVelocity();
    void updateAnimation();
    void updatePosition();
  private:
    void updateState(Input& input);

    State mState = State::Idle;
    bool mIsFacingRight = true;
    float mXVelocity = 0;
    float mYVelocity = 0;
};
#endif // PLAYER_H
