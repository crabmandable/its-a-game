#include "background.hpp"

Background::Background(std::string sheetName) {
  mSheetName = sheetName;
  //TODO figure out number of layers based on image height
  mNumberOfLayers = 5;
}

void Background::draw(Graphics& graphics) {
  SDL_Rect src, dest;
  src.x = src.y = dest.x = dest.y = 0;
  src.w = dest.w = Graphics::SCREEN_WIDTH;
  src.h = dest.h = Graphics::SCREEN_HEIGHT;

  for (int i = 0; i < mNumberOfLayers; i++) {
    graphics.drawTexture(Graphics::RenderLayer::Background, mSheetName, src, dest);
    src.y += Graphics::SCREEN_HEIGHT;
  }
}
