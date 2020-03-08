#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include "graphics.hpp"
class Checkpoint {
  public:
    Checkpoint(int col, int row, int width, int height, int spawnOffsetCol, int spawnOffsetRow);
    void getSpawn(int& x, int& y);
    bool pointIsInCheckpoint(int x, int y);

  private:
    int mOriginX;
    int mOriginY;
    int mHeight;
    int mWidth;
    int mSpawnOffsetX;
    int mSpawnOffsetY;
};
#endif
