#ifndef ASSET_H
#define ASSET_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "geometry.hpp"
class Asset {
  public:
    static std::string getAssetPath(const std::string &subDir = "");

    Asset(std::string fileName, Size size, SDL_Renderer* renderer);
    ~Asset();

    SDL_Texture* texture();
    Size size();

  private:
    SDL_Texture* mTexture{nullptr};
    Size mSize;
};
#endif // ASSET_H
