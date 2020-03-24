#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "graphics.hpp"
#include "geometry.hpp"
class Background {
  public:
    Background() {};
    Background(std::string sheetName, int nLayers, Size size);
    void draw(Graphics& graphics);

  private:
    Size mSize;
    std::string mSheetName;
    int mNumberOfLayers;
};
#endif // BACKGROUND_H
