#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include "game_object.hpp"
#include "graphics.hpp"
#include "tinyxml2.hpp"
#include "collision.hpp"
#include "background.hpp"
#include "checkpoint.hpp"
#include "player.hpp"
class Room {
  public:

    /*
     * The room constructor loads the map file
     * the visible layers are initialized and other data is loaded for collision & map directives
     * All checkpoints should contain a spawn tile, surrounded by checkpoint tiles creating a rectangle
     * the start position for the player is loaded from the "start" layer - this layer should only contain 1 tile
     */
    Room(std::string name);
    Room();
    ~Room();
    void drawTiles(Graphics& graphics);
    void drawBackground(Graphics& graphics);
    void drawOverlay(Graphics& graphics);
    void getStart(int& x, int& y);
    void getCollisionEdgesNear(int x, int y, Collision::Orientation orientation, std::vector<Collision::CollisionEdge*> &edges);
    void adjustCamera(int &x, int &y);
    void affectPlayer(Player& player);

  private:
    const std::list<std::string> IGNORED_LAYERS = {"collision", "checkpoints", "start"};

    struct TileSet {
      int columns = 0;
      int tileCount = 0;
      int firstGID = 0;
      const char* src;
    };

    enum class Directive: unsigned int {
      Spawn = 0,
      Checkpoint = 1,
      Kill = 12,

      None,
    };

    void initLayers(tinyxml2::XMLDocument& mapFile);
    void initDirectives();
    bool isDrawnLayer(const char* layerName);
    void updateCheckpoint(Player& player);

    int mColumns;
    int mRows;
    int mWidth;
    int mHeight;
    std::vector<std::vector<std::vector<Sprite*>>> mTileLayers;
    std::vector<std::vector<unsigned int>> mCollisionMap;
    std::vector<std::vector<Directive>> mDirectivesMap;

    std::vector<Checkpoint*> mCheckpoints;

    int mStartX = 0;
    int mStartY = 0;

    Background mBackground;

    // Tint the room
    Uint8 mOverlayColor[4] = {32, 52, 68, 54}; //TODO read from file
};
#endif // ROOM_H
