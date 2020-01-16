#include "background.hpp"

Background::Background(std::string sheetName, int nLayers, int width, int height) {
  mSheetName = sheetName;
  mNumberOfLayers = nLayers;
  mHeight = height;
  mWidth = width;
}

void Background::draw(Graphics& graphics) {
  SDL_Rect src, dest;
  src.x = src.y = dest.x = dest.y = 0;
  src.w = dest.w = mWidth;
  src.h = dest.h = mHeight;

  Graphics::DrawConfig config;
  config.repeatX = true;
  config.repeatY = true;
  for (int i = 0; i < mNumberOfLayers; i++) {
    config.paralaxX = i * (1.0 / mNumberOfLayers);
    graphics.drawTexture(Graphics::RenderLayer::Background, mSheetName, src, dest, config);
    src.y += Graphics::SCREEN_HEIGHT;
  }
}
