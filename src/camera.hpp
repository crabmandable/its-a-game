#ifndef CAMERA_H
#define CAMERA_H
#include "graphics.hpp"
#include "player.hpp"
#include "room.hpp"
class Camera {
  public:
    Velocity kMaxVelocity{0.21, 0.30};
    Acceleration kDeccelerationFactor{0.01, 0.004};

    // how far ahead the camera should center when moving
    Position kAhead{20, 0};

    void updateTarget(Player& player, Room& room);
    void update(int elapsed_ms);
    void updateViewPort(Graphics& graphics);
    void setPosition(Position pos);
  private:
    Velocity mVelocity;
    Position mPosition{Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2};
    Position mTarget{Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2};
};
#endif
