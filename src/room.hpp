#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <sstream>
#include "game_object.hpp"
#include "graphics.hpp"
#include "tinyxml2.hpp"
#include "collision.hpp"
class Room {
  public:
    Room(std::string name);
    Room();
    ~Room();
    void drawTiles(Graphics& graphics);
    void getCollisionEdgesNear(int x, int y, Collision::Orientation orientation, std::vector<Collision::CollisionEdge*> &edges);

  private:
    struct TileSet {
      int columns = 0;
      int tileCount = 0;
      int firstGID = 0;
      const char* src;
    };

    void initLayers(tinyxml2::XMLDocument& mapFile);

    int mColumns;
    int mRows;
    int mWidth;
    int mHeight;
    bool mDrawCollision = false;
    std::vector<std::vector<std::vector<Sprite*>>> mTileLayers;
    std::vector<std::vector<unsigned int>> mCollisionMap;
};
#endif // ROOM_H
