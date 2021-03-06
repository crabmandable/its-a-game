#ifndef COLLISION_H
#define COLLISION_H
#include <algorithm>
#include <math.h>
#include <iostream>
#include "graphics.hpp"
namespace Collision {
  static const int kCollisionCheckTileRadius = 4;

  enum class Orientation {
    X, // when x constant and y changes (like a y axis)
    Y // when y is constant and x changes (like an x axis)
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
    Velocity velocity;
    Position origin;
    int length = 0;

    // returns the origin coordinate of the orientation
    bool directionIsPositive();
    bool directionIsNegative();
    float parallelVelocity();
    void draw(Graphics& graphics, bool blue = false);
  };

  Vector2D detectCollision(CollisionEdge &e1, CollisionEdge &e2, int elapsed_ms);

  //[right, top, left, bottom]
  static const unsigned int collisionTileMap[77][4] = {
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

    // tenth row
    {0x1, 0x2, 0x0, 0x0},
    {0x0, 0x2, 0x1, 0x0},
    {0x2, 0x1, 0x0, 0x0},
    {0x0, 0x1, 0x2, 0x0},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},

    // eleventh row
    {0x1, 0x0, 0x0, 0x2},
    {0x0, 0x0, 0x1, 0x2},
    {0x2, 0x0, 0x0, 0x1},
    {0x0, 0x0, 0x2, 0x1},
    // padding
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
  };
}
#endif // COLLISION_H
