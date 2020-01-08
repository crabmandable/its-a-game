#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "graphics.hpp"
class Background {
  public:
    Background() {};
    Background(std::string sheetName);
    void draw(Graphics& graphics);

  private:
    std::string mSheetName;
    int mNumberOfLayers;
};
#endif // BACKGROUND_H
