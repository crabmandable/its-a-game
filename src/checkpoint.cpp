#include "checkpoint.hpp"

Checkpoint::Checkpoint(Rect rect, Position spawnOffset) {
  mRect = rect;
  mSpawnOffset = spawnOffset;
}

Position Checkpoint::getSpawn() {
  return mRect.origin + mSpawnOffset;
}

bool Checkpoint::pointIsInCheckpoint(Position p) {
  return mRect.containsPoint(p);
} 
