#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include "animated_sprite.hpp"
#include "collision.hpp"
#include "checkpoint.hpp"
#include "geometry.hpp"

class Player : public GameObject {
  public:
    const float kAcceleration = 0.002;
    const float kDeceleration = 0.00115;
    const float kJumpDeceleration = 0.0009;
    const float kMaxSpeed = 0.105;
    const float kJumpForce = 0.25;
    const float kJumpLength_ms = 250;
    const float kGravity = 0.0023;

    const int kRespawnTime_ms = 1000;

    const Position kCollisionLength{35, 2};
    const Position kCollisionOverhang{0, 0};
    const Position kCollisionOffset{11, 0};

    enum class Event {
      Death,
      Respawn,
      InputUnlocked,
      InputLocked,
    };

    enum class State {
      Idle,
      Running,
      Jumping,
      Falling,
      Dead
    };

    enum class DeathType {
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
    std::vector<Event>* getEvents();
    State getState();
    void isGrounded(bool grounded);
    void goToCheckpoint();
    void setCheckpoint(Checkpoint* checkpoint);
    void killPlayer(DeathType t);
    void lockInput(int time_ms);

  protected:
    Sprite* getSprite();

  private:
    void updateState(Input& input, int elapsed_ms);
    void updateCollisionEdges();

    AnimatedSprite mSprite;
    State mState = State::Idle;
    DeathType mDeath = DeathType::Falling;
    bool mIsFacingRight = true;
    bool mGrounded = false;
    Velocity mVelocity;

    int mDirection = 0;
    int mJumpElapsed = 0;
    int mDeathElapsed = 0;
    Checkpoint* mCheckpoint = nullptr;

    Collision::CollisionEdge mCollisionEdges[4];

    std::vector<Event> mEvents;
    int mInputLock_ms = 0;
};
#endif // PLAYER_H
