#include "room.hpp"
using std::vector;
Room::~Room() {
}

void Room::drawTiles(Graphics& graphics) {
  for (int layer = 0; layer < (int)mTileLayers.size(); layer++) {
    for (int row = 0; row < (int)mTileLayers[layer].size(); row++) {
      for (int col = 0; col < (int)mTileLayers[layer][row].size(); col++) {
        if (Sprite* s = mTileLayers[layer][row][col]) {
          graphics.drawTile(s->getSpriteSheet(), s->getSpriteLocation(), col, row);
        }
      }
    }
  }
}

Room::Room(std::string name) {
  using namespace tinyxml2;
  XMLDocument mapFile;
  std::string mapPath = Graphics::getResourcePath("maps") + name;
  std::cout << "loading map file: " << mapPath << std::endl;
  mapFile.LoadFile(mapPath.c_str());
  if (!mapFile.FirstChild()) {
    std::cout << "unable to load map from " << mapPath << std::endl;
    return;
  }

  initLayers(mapFile);

  // load up the tile mappings so we can init sprites
  XMLElement* tileset = mapFile.FirstChildElement("map")->FirstChildElement("tileset");

  int minGID = 9000;
  vector<TileSet*> tileSets;
  do {
    TileSet* t = new TileSet();
    tileset->QueryIntAttribute("columns", &t->columns);
    tileset->QueryIntAttribute("tilecount", &t->tileCount);
    tileset->QueryIntAttribute("firstgid", &t->firstGID);
    tileset->FirstChildElement("image")->QueryStringAttribute("source", &t->src);
    tileSets.push_back(t);
    minGID = std::min(minGID, t->firstGID);
  } while ((tileset = tileset->NextSiblingElement("tileset")));

  // loop through layers and load up the sprites
  XMLElement* layer = mapFile.FirstChildElement("map")->FirstChildElement("layer");
  int layerIdx = 0;
  do {
    const char* name;
    layer->QueryStringAttribute("name", &name);
    std::cout << "Loading layer: " << name << std::endl;
    bool isCollisionLayer = 0 == strcmp("collision", name);

    std::stringstream bgData(layer->FirstChildElement("data")->GetText());
    std::string line;
    //start from -1 because data includes an empty line
    for (int row = -1; std::getline(bgData, line, '\n'); row++) {
      size_t pos = 0;
      for (int col = 0; (pos = line.find(',')) != std::string::npos; col++) {
        std::string token = line.substr(0, pos);
        line.erase(0, pos + 1);
        int gID =  std::stoi(token);

        if (gID < minGID) continue;
        
        size_t i;
        for (i = 0; i < tileSets.size() ; i++) {
          if (gID < tileSets[i]->firstGID) {
            break;
          }
        }
        i--;

        TileSet* tileset = tileSets[i];

        if (isCollisionLayer) {
          mCollisionMap[row][col] = gID + 1 - tileset->firstGID;
          if (!mDrawCollision) continue;
        }

        int id = gID - tileset->firstGID;
        int tileRow = id / tileset->columns;
        int tileCol = id % tileset->columns;

        std::string src = std::string(tileset->src);
        src = src.substr(src.find("/"));
        Sprite* s = new Sprite(src, tileCol * Graphics::TILE_SIZE, tileRow * Graphics::TILE_SIZE, Graphics::TILE_SIZE, Graphics::TILE_SIZE);
        mTileLayers[layerIdx][row][col] = s;
      }
    }
    layerIdx++;
  } while ((layer = layer->NextSiblingElement("layer")));

  for (auto t: tileSets) {
    delete t;
  }
}

void Room::initLayers(tinyxml2::XMLDocument& mapFile) {
  mapFile.FirstChildElement("map")->QueryIntAttribute("width", &mColumns);
  mapFile.FirstChildElement("map")->QueryIntAttribute("height", &mRows);

  // figure out how many layers we need to draw
  int layers = 0;
  tinyxml2::XMLElement* l = mapFile.FirstChildElement("map")->FirstChildElement("layer");
  do {
    const char* name;
    l->QueryStringAttribute("name", &name);
    if (mDrawCollision || 0 != strcmp(name, "collision")) {
      layers++;
    }
  } while ((l = l->NextSiblingElement("layer")));

  mWidth = mColumns * Graphics::TILE_SIZE;
  mHeight = mRows * Graphics::TILE_SIZE;

  //init layers
  for (int i = 0; i < layers; i++) {
    mTileLayers.push_back(vector<vector<Sprite*>>(mRows, vector<Sprite*>(mColumns, nullptr)));
  }
  mCollisionMap = vector<vector<unsigned int>>(mRows, vector<unsigned int>(mColumns, 0x0));
}

void Room::getCollisionEdgesNear(int x, int y, Collision::Orientation orientation, std::vector<Collision::CollisionEdge*> &edges) {
  using namespace Collision;
  edges.clear();
  x = std::max(x / Graphics::TILE_SIZE - kCollisionCheckTileRadius, 0);
  y = std::max(y / Graphics::TILE_SIZE - kCollisionCheckTileRadius, 0);
  for (int i = y; i < mRows && i < y + (kCollisionCheckTileRadius * 2) + 1; i++) {
    for (int j = x; j < mColumns && j < x + (kCollisionCheckTileRadius * 2) + 1; j++) {
      // look up tile in tile map
      for (int k = orientation == Orientation::X ? 0 : 1; k < 4; k+=2) {
      // (void)orientation;
      // for (int k = 0; k < 4; k++) {
        if (unsigned int dir = collisionTileMap[mCollisionMap[i][j]][k]) {
          CollisionEdge* e = new CollisionEdge();
          e->direction = (CollisionDirection)dir;
          e->orientation = k % 2 ? Orientation::Y : Orientation::X;
          e->originX = j * Graphics::TILE_SIZE + (k == 2 ? Graphics::TILE_SIZE : 0);
          e->originY = i * Graphics::TILE_SIZE + (k == 3 ? Graphics::TILE_SIZE : 0);
          e->length = Graphics::TILE_SIZE;
          edges.push_back(e);
        }
      }
    }
  }
}

