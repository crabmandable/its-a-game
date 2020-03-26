#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <algorithm>
#include "animated_sprite.hpp"
#include "collision.hpp"
#include "checkpoint.hpp"
#include "geometry.hpp"

class Player : public GameObject {
  public:
    const float kAcceleration = 0.003;
    const float kDeceleration = 0.00115;
    const float kJumpDeceleration = 0.0009;
    const float kMaxSpeed = 0.13;
    const float kJumpForce = 0.25;
    const float kJumpLength_ms = 250;
    const float kGravity = 0.0023;

    const Position kCollisionLength{35, 2};
    const Position kCollisionOverhang{0, 0};
    const Position kCollisionOffset{11, 0};

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

    Collision::CollisionEdge* getCollisionEdge(int idx);

    void incrementPosition(Vector2D delta);
    void setPosition(Position p);
    Position getPosition();
    Velocity getVelocity();
    bool getFacing();
    State getState();
    void isGrounded(bool grounded);
    void goToCheckpoint();

    void setCheckpoint(Checkpoint* checkpoint);
  protected:
    Sprite* getSprite();

  private:
    void updateState(Input& input, int elapsed_ms);
    void updateCollisionEdges();

    AnimatedSprite mSprite;
    State mState = State::Idle;
    bool mIsFacingRight = true;
    bool mGrounded = false;
    Velocity mVelocity;

    int mDirection = 0;
    int mJumpElapsed = 0;
    Checkpoint* mCheckpoint = nullptr;

    Collision::CollisionEdge mCollisionEdges[4];
};
#endif // PLAYER_H
