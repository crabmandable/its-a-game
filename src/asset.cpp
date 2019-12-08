#include "asset.hpp"

Asset::Asset(std::string fileName, int width, int height, SDL_Renderer* renderer) {
  mWidth = width;
  mHeight = height;
  std::string subdir = "";
  std::string baseName = fileName;
  if (fileName.find("/") != std::string::npos) {
     subdir = fileName.substr(0, fileName.find("/"));
     baseName = fileName.substr(fileName.find("/"));
  }
  std::string dir = getAssetPath(subdir);
  std::string fullPath = dir + baseName;
  mTexture = IMG_LoadTexture(renderer, fullPath.c_str());
  if (!mTexture) {
    std::cout << "Error loading bmp:" << fullPath << std::endl;
    std::cout << SDL_GetError() << std::endl;
  } else {
    std::cout << "Loaded bmp:" << fullPath << std::endl;
  }
}

Asset::~Asset() {
  if (mTexture) SDL_DestroyTexture(mTexture);
}

SDL_Texture* Asset::texture() {
  return mTexture;
}

int Asset::height() {
  return mHeight;
}

int Asset::width() {
  return mWidth;
}

std::string Asset::getAssetPath(const std::string &subDir) {
#ifdef _WIN32
  const char PATH_SEP = '\\';
#else
  const char PATH_SEP = '/';
#endif

  //This will hold the base resource path: Lessons/res/
  //We give it static lifetime so that we'll only need to call
  //SDL_GetBasePath once to get the executable path
  static std::string baseRes;
  if (baseRes.empty()){
    //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
    char *basePath = SDL_GetBasePath();
    if (basePath){
      baseRes = basePath;
      SDL_free(basePath);
    }
    else {
      std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
      return "";
    }
    //We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.rfind("bin");
    baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
  }
  //If we want a specific subdirectory path in the resource directory
  //append it to the base path. This would be something like Lessons/res/Lesson0
  return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
};
