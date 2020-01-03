#ifndef COLLISION_H
#define COLLISION_H
#include <algorithm>
#include <math.h>
#include <iostream>
#include "graphics.hpp"
namespace Collision {
  static const int kCollisionCheckTileRadius = 4;

  enum class Orientation {
    X,
    Y
  };

  enum class CollisionDirection : unsigned {
    None = 0x0,
    Both = 0x3,
    Positive = 0x1,
    Negative = 0x2
  };

  struct CollisionEdge {
    Orientation orientation = Orientation::X;
    CollisionDirection direction = CollisionDirection::Both;
    float velocityX = 0;
    float velocityY = 0;
    int originX = 0;
    int originY = 0;
    int length = 0;

    // returns points that make up the line perpendicular to the orientation
    void getPerpendicularPoints(float &p1, float &p2, int elapsed_ms);
    // returns the origin coordinate of the orientation
    float getParallelPoint();
    bool directionIsPositive();
    bool directionIsNegative();
    float perpendicularVelocity();
    float parallelVelocity();
    void draw(Graphics& graphics, bool blue = false);
  };

  void detectCollision(CollisionEdge &e1, CollisionEdge &e2, int elapsed_ms, int &deltaX, int &deltaY);

  //[right, top, left, bottom]
  static const unsigned int collisionTileMap[55][4] = {
    //padding
    {0x0, 0x0, 0x0, 0x0},

    // first row
    {0x0, 0x3, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x3},
    {0x3, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x3, 0x0},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // second row
    {0x3, 0x0, 0x0, 0x3},
    {0x0, 0x0, 0x3, 0x3},
    {0x3, 0x0, 0x3, 0x0},
    {0x0, 0x3, 0x0, 0x3},
    {0x3, 0x3, 0x0, 0x0},
    {0x0, 0x3, 0x3, 0x0},

    // third row
    {0x3, 0x3, 0x3, 0x0},
    {0x3, 0x0, 0x3, 0x3},
    {0x3, 0x3, 0x0, 0x3},
    {0x0, 0x3, 0x3, 0x3},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // forth row
    {0x3, 0x3, 0x3, 0x3},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // fith row
    {0x0, 0x1, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x1},
    {0x1, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x1, 0x0},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // sixth row
    {0x0, 0x2, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x2},
    {0x2, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x2, 0x0},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // seventh row
    {0x1, 0x0, 0x0, 0x1},
    {0x0, 0x0, 0x1, 0x1},
    {0x1, 0x0, 0x1, 0x0},
    {0x0, 0x1, 0x0, 0x1},
    {0x1, 0x1, 0x0, 0x0},
    {0x0, 0x1, 0x1, 0x0},

    // eigth row
    {0x2, 0x0, 0x0, 0x2},
    {0x0, 0x0, 0x2, 0x2},
    {0x2, 0x0, 0x2, 0x0},
    {0x0, 0x2, 0x0, 0x2},
    {0x2, 0x2, 0x0, 0x0},
    {0x0, 0x2, 0x2, 0x0},
    
    // ninth row
    {0x2, 0x2, 0x2, 0x0},
    {0x2, 0x0, 0x2, 0x2},
    {0x2, 0x2, 0x0, 0x2},
    {0x0, 0x2, 0x2, 0x2},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
  };
}
#endif // COLLISION_H
