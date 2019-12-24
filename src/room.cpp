#include "room.hpp"
using std::vector;
Room::~Room() {
}

void Room::drawTiles(Graphics& graphics, int elapsed_ms) {
  for (int layer = 0; layer < (int)mTileLayers.size(); layer++) {
    for (int row = 0; row < (int)mTileLayers[layer].size(); row++) {
      for (int col = 0; col < (int)mTileLayers[layer][row].size(); col++) {
        if (Sprite* s = mTileLayers[layer][row][col]) {
          s->drawNextFrame(col * kTileSize, row * kTileSize, graphics, elapsed_ms);
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

  int cols = 0;
  mapFile.FirstChildElement("map")->QueryIntAttribute("width", &cols);

  int rows = 0;
  mapFile.FirstChildElement("map")->QueryIntAttribute("height", &rows);

  int layers = 0;
  XMLElement* l = mapFile.FirstChildElement("map")->FirstChildElement("layer");
  do { layers++; } while ((l = l->NextSiblingElement("layer")));

  setSize(cols, rows, layers);

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

  XMLElement* layer = mapFile.FirstChildElement("map")->FirstChildElement("layer");
  int layerIdx = 0;
  do {
    const char* name;
    layer->QueryStringAttribute("name", &name);
    std::cout << "Loading layer: " << name << std::endl;

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
        int id = gID - tileset->firstGID;
        int tileRow = id / tileset->columns;
        int tileCol = id % tileset->columns;

        std::string src = std::string(tileset->src);
        src = src.substr(src.find("/"));
        Sprite* s = new Sprite(src, tileCol * kTileSize, tileRow * kTileSize, kTileSize, kTileSize);
        mTileLayers[layerIdx][row][col] = s;
      }
    }
    layerIdx++;
  } while ((layer = layer->NextSiblingElement("layer")));

  for (auto t: tileSets) {
    delete t;
  }
}

void Room::setSize(int columns, int rows, int layers) {
  mWidth = columns * kTileSize;
  mHeight = rows * kTileSize;
  mColumns = columns;
  mRows = rows;
  for (int i = 0; i < layers; i++) {
    mTileLayers.push_back(vector<vector<Sprite*>>(mRows, vector<Sprite*>(mColumns, nullptr)));
  }
}
