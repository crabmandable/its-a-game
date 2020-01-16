#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "graphics.hpp"
class Background {
  public:
    Background() {};
    Background(std::string sheetName, int nLayers, int width, int height);
    void draw(Graphics& graphics);

  private:
    int mHeight;
    int mWidth;
    std::string mSheetName;
    int mNumberOfLayers;
};
#endif // BACKGROUND_H
