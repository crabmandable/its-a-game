#ifndef CAMERA_H
#define CAMERA_H
#include "graphics.hpp"
#include "player.hpp"
#include "room.hpp"
class Camera {
  public:
    float kMaxXVelocity = 0.21;
    float kMaxYVelocity = 0.30;
    float kXDeccelerationFactor = 0.01;
    float kYDeccelerationFactor = 0.004;

    // how far ahead the camera should center when moving
    int kXAhead = 20;
    int kYAhead = 0;

    void updateTarget(Player& player, Room& room);
    void update(int elapsed_ms);
    void updateViewPort(Graphics& graphics);
    void setPosition(int x, int y);
  private:
    float mXVelocity = 0;
    float mYVelocity = 0;
    int mXPos = Graphics::SCREEN_WIDTH / 2;
    int mYPos = Graphics::SCREEN_HEIGHT / 2;
    int mTargetX = Graphics::SCREEN_WIDTH / 2;
    int mTargetY = Graphics::SCREEN_HEIGHT / 2;
};
#endif
