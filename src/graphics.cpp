#include "graphics.hpp"

Graphics::Graphics() {
}

Graphics::~Graphics() {
  for (auto& it: mTextures) {
    SDL_DestroyTexture(it.second);
  }
  if (mRenderer) SDL_DestroyRenderer(mRenderer); 
  if (mWindow) SDL_DestroyWindow(mWindow);
}

std::string Graphics::getResourcePath(const std::string &subDir) {
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
}

void Graphics::init() {
  if (SDL_CreateWindowAndRenderer(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_RESIZABLE,
    &mWindow,
    &mRenderer
  )) {
    std::cout << "Unable to create SDL_Window:" << SDL_GetError() << std::endl;
    return;
  }
}

void Graphics::loadTexture(std::string path) {
  std::string subdir = "";
  std::string baseName = path;
  if (path.find("/") != std::string::npos) {
     subdir = path.substr(0, path.find("/"));
     baseName = path.substr(path.find("/"));
  }
  std::string dir = getResourcePath(subdir);
  std::string fullPath = dir + baseName;
  SDL_Texture* texture = IMG_LoadTexture(mRenderer, fullPath.c_str());
  if (!texture) {
    std::cout << "Error loading img:" << fullPath << std::endl;
    std::cout << SDL_GetError() << std::endl;
  } else {
    std::cout << "Loaded img:" << fullPath << std::endl;
  }
  mTextures.insert({path, texture});
}

void Graphics::destroyTexture(std::string path) {
  SDL_DestroyTexture(mTextures[path]);
}

void Graphics::updateWindowSize() {
  SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
  if (mWindowWidth / WIDTH_RATIO > mWindowHeight / HEIGHT_RATIO) {
    mWindowScale = (float)mWindowHeight / SCREEN_HEIGHT;
  } else {
    mWindowScale  = (float)mWindowWidth/ SCREEN_WIDTH;
  }
}

void Graphics::beginDraw() {
  updateWindowSize();
  SDL_RenderClear(mRenderer);
}

void Graphics::present() {
  SDL_RenderPresent(mRenderer);
}

void Graphics::drawTexture(std::string path, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip flip) {
    if (mTextures.find(path) == mTextures.end()) {
      loadTexture(path);
    }

    dest.w = dest.w * mWindowScale;
    dest.h = dest.h * mWindowScale;
    dest.x = mWindowScale *  dest.x;
    dest.y = mWindowScale * dest.y;
    SDL_RenderCopyEx(mRenderer, mTextures[path], &src, &dest, 0, NULL, flip);
}
