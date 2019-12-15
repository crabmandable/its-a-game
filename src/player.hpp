#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <algorithm>
class Player : public GameObject {
  public:
    const float kAcceleration = 0.015;
    const float kDeceleration = 0.00175;
    const float kJumpDeceleration = 0.0009;
    const float kMaxSpeed = 0.4;
    const float kJumpForce = 0.90;
    const float kJumpLength_ms = 200;
    const float kGravity = 0.0048;

    enum class State {
      Idle,
      Running,
      Jumping,
      Falling
    };


    Player();
    void update(Input& input, int elapsed_ms);
    void updateXVelocity(int elapsed_ms);
    void updateYVelocity(int elapsed_ms);
    void updateAnimation();
    void updatePosition(int elapsed_ms);
  private:
    void updateState(Input& input, int elapsed_ms);

    State mState = State::Idle;
    bool mIsFacingRight = true;
    bool mGrounded = false;
    float mXVelocity = 0;
    float mYVelocity = 0;

    int mDirection = 0;
    int mJumpElapsed = 0;
};
#endif // PLAYER_H
