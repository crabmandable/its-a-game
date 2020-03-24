#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include "graphics.hpp"
#include "geometry.hpp"
class Checkpoint {
  public:
    Checkpoint(Rect rect, Position spawnOffset);
    Position getSpawn();
    bool pointIsInCheckpoint(Position p);

  private:
    Rect mRect;
    Position mSpawnOffset;
};
#endif
