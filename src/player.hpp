#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <algorithm>
#include "animated_sprite.hpp"
class Player : public GameObject {
  public:
    const float kAcceleration = 0.015;
    const float kDeceleration = 0.00175;
    const float kJumpDeceleration = 0.0009;
    const float kMaxSpeed = 0.22;
    const float kJumpForce = 0.55;
    const float kJumpLength_ms = 150;
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

  protected:
    Sprite* getSprite();

  private:
    void updateState(Input& input, int elapsed_ms);

    AnimatedSprite mSprite;
    State mState = State::Idle;
    bool mIsFacingRight = true;
    bool mGrounded = false;
    float mXVelocity = 0;
    float mYVelocity = 0;

    int mDirection = 0;
    int mJumpElapsed = 0;
};
#endif // PLAYER_H
