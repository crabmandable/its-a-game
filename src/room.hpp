#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <sstream>
#include "game_object.hpp"
#include "graphics.hpp"
#include "tinyxml2.hpp"
class Room {
  public:
    static const int kTileSize{16};

    Room(std::string name);
    Room();
    ~Room();
    void drawTiles(Graphics& graphics, int elapsed_ms);
    void setSize(int columns, int rows, int layers);

  private:
    struct TileSet {
      int columns = 0;
      int tileCount = 0;
      int firstGID = 0;
      const char* src;
    };

    int mColumns;
    int mRows;
    int mWidth;
    int mHeight;
    std::vector<std::vector<std::vector<Sprite*>>> mTileLayers;
};
#endif // ROOM_H
