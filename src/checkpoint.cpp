#include "checkpoint.hpp"

Checkpoint::Checkpoint(int col, int row, int width, int height, int spawnOffsetCol, int spawnOffsetRow) {
  mOriginX = col * Graphics::TILE_SIZE;
  mOriginY = row * Graphics::TILE_SIZE;
  mWidth = width * Graphics::TILE_SIZE;
  mHeight = height * Graphics::TILE_SIZE;
  mSpawnOffsetX = spawnOffsetCol * Graphics::TILE_SIZE;
  mSpawnOffsetY = spawnOffsetRow * Graphics::TILE_SIZE;
}

void Checkpoint::getSpawn(int& x, int& y) {
  x = mOriginX + mSpawnOffsetX;
  y = mOriginY + mSpawnOffsetY;
}

bool Checkpoint::pointIsInCheckpoint(int x, int y) {
  return x >= mOriginX && x <= mOriginX + mWidth
    && y >= mOriginY && y <= mOriginY + mHeight;
} 
