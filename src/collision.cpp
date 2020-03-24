#include "collision.hpp"

Vector2D Collision::detectCollision(CollisionEdge &e1, CollisionEdge &e2, int elapsed_ms) {
  // Unless the edges have the same orientation they cannot be colliding
  if (e1.orientation != e2.orientation) return Vector2D();

  float delta = 0;

  // Unless the edges are moving towards each other in a direction consistent
  // with thier directionality, they cannot collide
  // e.g positive -> negative or negative <- positive
  float v = e1.parallelVelocity() - e2.parallelVelocity();
  if ((e1.directionIsPositive() && e2.directionIsNegative() && v >= 0)
      || (e1.directionIsNegative() && e2.directionIsPositive() && v <=0))
  {

    bool isXOrientation = e1.orientation == Orientation::X;

    FloatPosition e1Origin = (FloatPosition)e1.origin + (e1.velocity * elapsed_ms);
    FloatPosition e1End = e1Origin + FloatPosition(
        !isXOrientation ? e1.length : 0,
        isXOrientation ? e1.length : 0
        );

    FloatPosition e2Origin = (FloatPosition)e2.origin + (e2.velocity * elapsed_ms);
    FloatPosition e2End = e2Origin + FloatPosition(
        !isXOrientation ? e2.length : 0,
        isXOrientation ? e2.length : 0
        );

    if (isXOrientation) {
      // y will determine if the edges are in the same plane
      // Four scenarious:
      //
      //  ----    -----    ----    --
      //    ----   --    ----    -----
      //
      if ((e1Origin.y <= e2Origin.y && e1End.y >= e2End.y) ||
          (e1Origin.y <= e2Origin.y && e1End.y >= e2Origin.y) ||
          (e1Origin.y >= e2Origin.y && e1End.y <= e2End.y) ||
          (e1Origin.y <= e2End.y && e1End.y >= e2End.y))
      {
        // x will determine if the egdes have crossed each other
        if ((e1.origin.x <= e2.origin.x && e1Origin.x >= e2Origin.x) ||
          (e1.origin.x >= e2.origin.x && e1Origin.x <= e2Origin.x)) {
          delta = e1Origin.x - e2Origin.x;
        }
      }
    } else {
      // x will determine if the edges are in the same plane
      if ((e1Origin.x <= e2Origin.x && e1End.x >= e2End.x) ||
          (e1Origin.x <= e2Origin.x && e1End.x >= e2Origin.x) ||
          (e1Origin.x >= e2Origin.x && e1End.x <= e2End.x) ||
          (e1Origin.x <= e2End.x && e1End.x >= e2End.x))
      {
        // y will determine if the egdes have crossed each other
        if ((e1.origin.y <= e2.origin.y && e1Origin.y >= e2Origin.y) ||
          (e1.origin.y >= e2.origin.y && e1Origin.y <= e2Origin.y)) {
          delta = e1Origin.y - e2Origin.y;
        }
      }
    }
  }

  // round to up to nearest pixel
  if (delta > 0) {
    delta = ceil(delta);
  } else {
    delta = floor(delta);
  }

  if (e1.orientation == Orientation::X) {
    return Vector2D(delta, 0);
  } else {
    return Vector2D(0, delta);
  }
}

bool Collision::CollisionEdge::directionIsPositive() {
  return (bool)((int)CollisionDirection::Positive & (int)direction);
}

bool Collision::CollisionEdge::directionIsNegative() {
  return (bool)((int)CollisionDirection::Negative & (int)direction);
}

float Collision::CollisionEdge::parallelVelocity() {
  return orientation == Orientation::X ? velocity.x : velocity.y;
}

void Collision::CollisionEdge::draw(Graphics& graphics, bool blue) {
  Position end = origin + Position(orientation == Orientation::Y ? length : 0, orientation == Orientation::X ? length : 0);
  graphics.drawLine(origin, end, blue);
}
