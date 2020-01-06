#include "graphics.hpp"

Graphics::Graphics() {
}

Graphics::~Graphics() {
  for (auto& it: mTextures) {
    SDL_DestroyTexture(it.second);
  }
  if (mForegroundRenderer) SDL_DestroyRenderer(mForegroundRenderer);
  if (mForegroundSurface) SDL_FreeSurface(mForegroundSurface);
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

  SDL_SetWindowTitle(mWindow, "Zach's amazing game");

  if (!(mForegroundSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0))) {
    std::cout << "Unable to create tile surface:" << SDL_GetError() << std::endl;
    return;
  }

  Uint32 colorkey = SDL_MapRGB(mForegroundSurface->format, 0, 0, 0);
  SDL_SetColorKey(mForegroundSurface, SDL_TRUE, colorkey);

  if (!(mForegroundRenderer = SDL_CreateSoftwareRenderer(mForegroundSurface))) {
    std::cout << "Unable to create tile renderer:" << SDL_GetError() << std::endl;
    return;
  }
}

SDL_Texture* Graphics::getTexture(std::string path, RenderLayer layer) {
  std::string key = ((char)layer) + "|" + path;

  if (mTextures.find(key) != mTextures.end()) {
    return mTextures[key];
  }

  std::string subdir = "";
  std::string baseName = path;
  if (path.find("/") != std::string::npos) {
     subdir = path.substr(0, path.find("/"));
     baseName = path.substr(path.find("/"));
  }
  std::string dir = getResourcePath(subdir);
  std::string fullPath = dir + baseName;
  SDL_Texture* texture = IMG_LoadTexture(getRenderer(layer), fullPath.c_str());
  if (!texture) {
    std::cout << "Error loading img:" << fullPath << std::endl;
    std::cout << SDL_GetError() << std::endl;
  } else {
    std::cout << "Loaded img:" << fullPath << std::endl;
  }

  mTextures.insert({key, texture});
  return texture;
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
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);
  SDL_SetRenderDrawColor(mForegroundRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(mRenderer);
  SDL_RenderClear(mForegroundRenderer);
}

void Graphics::blitLayersToScreen() {
  SDL_Rect src, dest;
  dest.x = dest.y = src.y = src.x = 0;
  src.w = SCREEN_WIDTH;
  src.h = SCREEN_HEIGHT;

  dest.w = ceil(((float)SCREEN_WIDTH) * mWindowScale);
  dest.h = ceil(((float)SCREEN_HEIGHT) * mWindowScale);

  SDL_Texture* t = SDL_CreateTextureFromSurface(mRenderer, mForegroundSurface);
  SDL_RenderCopy(mRenderer, t, &src, &dest);
  SDL_DestroyTexture(t);
}

void Graphics::present() {
  SDL_RenderPresent(mRenderer);
}

void Graphics::drawTile(std::string tileSheetPath, SDL_Rect src, int column, int row) {
  SDL_Texture* texture = getTexture(tileSheetPath, RenderLayer::Foreground);

  SDL_Rect dest;
  src.w = src.h = dest.h = dest.w = TILE_SIZE;
  dest.x = column * TILE_SIZE;
  dest.y = row * TILE_SIZE;
  SDL_RenderCopy(mForegroundRenderer, texture, &src, &dest);
}

void Graphics::drawTexture(RenderLayer layer, std::string path, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip flip) {
  SDL_Texture* texture = getTexture(path, layer);
  SDL_RenderCopyEx(getRenderer(layer), texture, &src, &dest, 0, NULL, flip);
}

SDL_Renderer* Graphics::getRenderer(RenderLayer layer) {
  switch(layer) {
    case RenderLayer::Foreground:
    default:
      return mForegroundRenderer;
  }
}

void Graphics::drawLine(int x1, int y1, int x2, int y2, bool blue) {
  if (blue) {
    SDL_SetRenderDrawColor(mRenderer, kBlueLineColor[0], kBlueLineColor[1], kBlueLineColor[2], kBlueLineColor[3]);
  } else {
    SDL_SetRenderDrawColor(mRenderer, kLineColor[0], kLineColor[1], kLineColor[2], kLineColor[3]);
  }
  SDL_RenderDrawLine(mRenderer, x1 * mWindowScale, y1 * mWindowScale, x2 * mWindowScale, y2 * mWindowScale);
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);
}
