#include "collision.hpp"

void Collision::detectCollision(CollisionEdge &e1, CollisionEdge &e2, int elapsed_ms, int &deltaX, int &deltaY) {
  deltaX = 0;
  deltaY = 0;
  float delta = 0;
  if (e1.orientation != e2.orientation) return;
  float v = e1.parallelVelocity() - e2.parallelVelocity();
  if ((e1.directionIsPositive() && e2.directionIsNegative() && v > 0) || (e1.directionIsNegative() && e2.directionIsPositive() && v < 0)) {
    float e1P1, e1P2;
    e1.getPerpendicularPoints(e1P1, e1P2, elapsed_ms);
    float e2P1, e2P2;
    e2.getPerpendicularPoints(e2P1, e2P2, elapsed_ms);
    if ((e1P1 < e2P1 && e1P2 > e2P2) || (e1P1 >= e2P1 && e1P1 <= e2P2) || (e1P2 >= e2P1 && e1P2 <= e2P2)) {
      float p1Before = e1.getParallelPoint();
      float p2Before = e2.getParallelPoint();
      float p1After = p1Before + (elapsed_ms * e1.parallelVelocity());
      float p2After = p2Before + (elapsed_ms * e2.parallelVelocity());

      if (p1Before <= p2Before) {
        if (p1After > p2After) {
          //collision!!
          delta = ceil(p1After - p2After);
        }
      } else if (p1Before >= p2Before) {
        if (p1After < p2After) {
          //collision!
          delta = floor(p1After - p2After);
        }
      }
    }
  }

  if (e1.orientation == Orientation::X) {
    deltaX = delta;
  } else {
    deltaY = delta;
  }
}

void Collision::CollisionEdge::getPerpendicularPoints(float &p1, float &p2, int elapsed_ms) {
  if (orientation == Orientation::X) {
    p1 = originY + (velocityY * elapsed_ms);
  } else {
    p1 = originX + (velocityX * elapsed_ms);
  }
  p2 = p1 + length;
}

float Collision::CollisionEdge::getParallelPoint() {
  return orientation == Orientation::X ? originX : originY;
}

bool Collision::CollisionEdge::directionIsPositive() {
  return (bool)((int)CollisionDirection::Positive & (int)direction);
}

bool Collision::CollisionEdge::directionIsNegative() {
  return (bool)((int)CollisionDirection::Negative & (int)direction);
}

float Collision::CollisionEdge::perpendicularVelocity() {
  return orientation == Orientation::X ? velocityY : velocityX;
}

float Collision::CollisionEdge::parallelVelocity() {
  return orientation == Orientation::X ? velocityX : velocityY;
}

void Collision::CollisionEdge::draw(Graphics& graphics, bool blue) {
  int xlen = orientation == Orientation::Y ? length : 0;
  int ylen = orientation == Orientation::X ? length : 0;
  graphics.drawLine(originX, originY, originX + xlen, originY + ylen, blue);
}
