#ifndef ASSET_H
#define ASSET_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
class Asset {
  public:
    static std::string getAssetPath(const std::string &subDir = "");

    Asset(std::string fileName, int width, int height, SDL_Renderer* renderer);
    ~Asset();

    SDL_Texture* texture();
    int height();
    int width();

  private:
    SDL_Texture* mTexture{nullptr};
    int mHeight, mWidth;
};
#endif // ASSET_H
