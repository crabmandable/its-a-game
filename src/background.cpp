#include "background.hpp"

Background::Background(std::string sheetName, int nLayers, Size size) {
  mSheetName = sheetName;
  mNumberOfLayers = nLayers;
  mSize = size;
}

void Background::draw(Graphics& graphics) {
  Rect src, dest;
  src.size = dest.size = mSize;

  Graphics::DrawConfig config;
  config.repeatX = true;
  config.repeatY = true;
  for (int i = 0; i < mNumberOfLayers; i++) {
    config.paralaxX = i * (1.0 / mNumberOfLayers);
    graphics.drawTexture(Graphics::RenderLayer::Background, mSheetName, src, dest, config);
    src.origin.y += mSize.h;
  }
}
