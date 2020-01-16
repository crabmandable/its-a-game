#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <fstream>
#include <sstream>
#include "game_object.hpp"
#include "graphics.hpp"
#include "tinyxml2.hpp"
#include "collision.hpp"
#include "background.hpp"
class Room {
  public:
    Room(std::string name);
    Room();
    ~Room();
    void drawTiles(Graphics& graphics);
    void drawBackground(Graphics& graphics);
    void drawOverlay(Graphics& graphics);
    void getCollisionEdgesNear(int x, int y, Collision::Orientation orientation, std::vector<Collision::CollisionEdge*> &edges);
    void adjustCamera(int &x, int &y);

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
    Background mBackground;

    // Uint8 mOverlayColor[4] = {162, 152, 68, 24}; //TODO read from file
    Uint8 mOverlayColor[4] = {32, 52, 68, 54}; //TODO read from file
};
#endif // ROOM_H
