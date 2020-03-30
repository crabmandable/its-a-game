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
    ScreenProperties::DEFAULT_WIDTH,
    ScreenProperties::DEFAULT_HEIGHT,
    SDL_WINDOW_RESIZABLE,
    &mWindow,
    &mRenderer
  )) {
    std::cout << "Unable to create SDL_Window:" << SDL_GetError() << std::endl;
    return;
  }

  SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
  SDL_SetWindowTitle(mWindow, "Zach's amazing game");

  if (!(mForegroundSurface = SDL_CreateRGBSurface(0,  kBufferSize.w + OVERBUFFER * 2, kBufferSize.h + OVERBUFFER * 2, 32, 0, 0, 0, 0))) {
    std::cout << "Unable to create tile surface:" << SDL_GetError() << std::endl;
    return;
  }

  // use black for foreground color key so that shadows get clipped to the drawn foreground
  Uint32 colorkey = SDL_MapRGB(mForegroundSurface->format, 0, 0, 0);
  SDL_SetColorKey(mForegroundSurface, SDL_TRUE, colorkey);

  if (!(mForegroundRenderer = SDL_CreateSoftwareRenderer(mForegroundSurface))) {
    std::cout << "Unable to create tile renderer:" << SDL_GetError() << std::endl;
    return;
  }

  if (!(mTransitionSurface = SDL_CreateRGBSurface(0,  kBufferSize.w, kBufferSize.h, 32, 0, 0, 0, 0))) {
    std::cout << "Unable to create tile surface:" << SDL_GetError() << std::endl;
    return;
  }

  // use white for transition color key so that we can draw in black
  colorkey = SDL_MapRGB(mTransitionSurface->format, 0xFF, 0xFF, 0xFF);
  SDL_SetColorKey(mTransitionSurface, SDL_TRUE, colorkey);

  if (!(mTransitionRenderer = SDL_CreateSoftwareRenderer(mTransitionSurface))) {
    std::cout << "Unable to create tile renderer:" << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetRenderDrawBlendMode(mTransitionRenderer, SDL_BLENDMODE_BLEND);
}

SDL_Texture* Graphics::getTexture(std::string path, RenderLayer layer) {
  std::string key = std::string(1, ((char)layer)) + "|" + path;

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
  Size size;
  SDL_GetWindowSize(mWindow, &size.w, &size.h);
  ScreenProperties::getInstance().setScreenSize(size);
}

void Graphics::beginDraw() {
  updateWindowSize();
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);
  SDL_SetRenderDrawColor(mForegroundRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_SetRenderDrawColor(mTransitionRenderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(mRenderer);
  SDL_RenderClear(mForegroundRenderer);
  SDL_RenderClear(mTransitionRenderer);
}

void Graphics::blitLayersToScreen() {
  blitForegroundToScreen();
  blitSurfaceToScreen(mTransitionSurface, mTransitionAlphaMod);
}

void Graphics::blitForegroundToScreen() {
  Size borders = ScreenProperties::getInstance().getBorderSize();
  SDL_Rect src, dest;
  src.y = src.x = 0;

  dest.x = borders.w;
  dest.y = borders.h;

  src.w = SCREEN_WIDTH + OVERBUFFER * 2;
  src.h = SCREEN_HEIGHT + OVERBUFFER * 2;

  dest.w = ceil(((float)src.w + OVERBUFFER * 2) * WINDOW_SCALE);
  dest.h = ceil(((float)src.h + OVERBUFFER * 2) * WINDOW_SCALE);
  
  // camera position is actually a decimal
  // we need to nudge after scaling to allow subpixel camera movement
  float xOffset = getViewPortOffset().x - floor(getViewPortOffset().x); 
  dest.x += (1 - xOffset > xOffset ? -xOffset : 1 - xOffset) * WINDOW_SCALE - OVERBUFFER;

  float yOffset = getViewPortOffset().y - floor(getViewPortOffset().y); 
  dest.y += (1 - yOffset > yOffset ? -yOffset : 1 - yOffset) * WINDOW_SCALE - OVERBUFFER;

  SDL_Texture* fgTexture = SDL_CreateTextureFromSurface(mRenderer, mForegroundSurface);
  SDL_RenderCopy(mRenderer, fgTexture, &src, &dest);
  SDL_DestroyTexture(fgTexture);
}

void Graphics::blitSurfaceToScreen(SDL_Surface* surface, Uint8 alphaMod) {
  Size borders = ScreenProperties::getInstance().getBorderSize();
  SDL_Rect src, dest;
  src.y = src.x = 0;
  dest.x = borders.w;
  dest.y = borders.h;

  src.w = SCREEN_WIDTH;
  src.h = SCREEN_HEIGHT;

  dest.w = src.w * WINDOW_SCALE;
  dest.h = src.h * WINDOW_SCALE;

  SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_SetTextureAlphaMod(texture, alphaMod);
  SDL_RenderCopy(mRenderer, texture, &src, &dest);
  SDL_DestroyTexture(texture);
}

void Graphics::present() {
  SDL_RenderPresent(mRenderer);
}

void Graphics::drawTile(std::string tileSheetPath, Rect src, int column, int row) {
  SDL_Texture* texture = getTexture(tileSheetPath, RenderLayer::Foreground);

  SDL_Rect dest;
  src.size.w = src.size.h = dest.h = dest.w = TILE_SIZE;
  dest.x = column * TILE_SIZE;
  dest.y = row * TILE_SIZE;

  DrawConfig config;
  draw(RenderLayer::Foreground, texture, src, dest, config);
}

void Graphics::drawTexture(RenderLayer layer, std::string path, Rect src, Rect dest, DrawConfig& config) {
  SDL_Texture* texture = getTexture(path, layer);
  draw(layer, texture, src, dest, config);
}

void Graphics::drawBackground(std::string path, SDL_Rect src, DrawConfig& config) {
  SDL_Renderer* renderer = getRenderer(RenderLayer::Background);
  SDL_Texture* texture = getTexture(path, RenderLayer::Background);
  Size borders = ScreenProperties::getInstance().getBorderSize();
  SDL_Rect dest = src;
  dest.w *= WINDOW_SCALE;
  dest.h *= WINDOW_SCALE;
  dest.x *= WINDOW_SCALE;
  dest.y *= WINDOW_SCALE;

  dest.x += borders.w;
  dest.y += borders.h;

  int screenW = SCREEN_WIDTH * WINDOW_SCALE;
  int screenH = SCREEN_HEIGHT * WINDOW_SCALE;

  dest.x -= roundl(config.paralaxX * getViewPortOffset().x * WINDOW_SCALE);
  dest.y -= roundl(config.paralaxY * getViewPortOffset().y * WINDOW_SCALE);

  if (config.repeatX || config.repeatY)
  {
    int startY = (dest.y % dest.h) - dest.h;
    int nY = ceil((abs(startY) + screenH) / (float) dest.h);
    int startX = (dest.x % dest.w) - dest.w;
    int nX = ceil((abs(startX) + screenW) / (float) dest.w);

    if (!config.repeatX && config.repeatY) //y repeat
    {
      if (dest.x < screenW && dest.x + dest.w > 0) {
        dest.x = startX;
        for (int i = 0; i < nX; i++) {
          SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, config.flip);
          dest.x += dest.w;
        }
      }
    }
    else if (!config.repeatY && config.repeatX) //x repeat
    {
      if (dest.y < screenH && dest.y + dest.h > 0) {
        dest.y = startY;
        for (int i = 0; i < nX; i++) {
          SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, config.flip);
          dest.y += dest.h;
        }
      }
    } else { // both repeat
        dest.x = startX;
        for (int i = 0; i < nX; i++) {
          dest.y = startY;
          for (int j = 0; j < nY; j++) {
            SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, config.flip);
            dest.y += dest.h;
          }
          dest.x += dest.w;
        }
    }
  } //only bother drawing textures that are in the screen
  else if ((dest.x < screenW && dest.x + dest.w > 0) && 
      (dest.y < screenH && dest.y + dest.h > 0))
  {
    SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, config.flip);
  }
}

void Graphics::draw(RenderLayer layer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, DrawConfig& config) {
  dest.x -= roundl(getViewPortOffset().x);
  dest.y -= roundl(getViewPortOffset().y);

  if ((dest.x < SCREEN_WIDTH + OVERBUFFER && dest.x + dest.w > -OVERBUFFER) && 
      (dest.y < SCREEN_HEIGHT + OVERBUFFER && dest.y + dest.h > -OVERBUFFER))
  {
    SDL_RenderCopyEx(getRenderer(layer), texture, &src, &dest, 0, NULL, config.flip);
  }
}

SDL_Renderer* Graphics::getRenderer(RenderLayer layer) {
  switch(layer) {
    case RenderLayer::Transition:
      return mTransitionRenderer;
    case RenderLayer::Background:
      return mRenderer;
    case RenderLayer::Foreground:
    default:
      return mForegroundRenderer;
  }
}

void Graphics::overlayColor(Uint8* color) {
  (void) color;
  SDL_SetRenderDrawColor(mRenderer, color[0], color[1], color[2], color[3]);
  Size borders = ScreenProperties::getInstance().getBorderSize();
  SDL_Rect rect;
  rect.x = borders.w;
  rect.y = borders.h;
  rect.w = SCREEN_WIDTH * WINDOW_SCALE;
  rect.h = SCREEN_HEIGHT * WINDOW_SCALE;
  SDL_RenderFillRect(mRenderer, &rect);
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);
}

void Graphics::drawLine(Position p1, Position p2, bool blue) {
  p1 -= getViewPortOffset();
  p1 *= WINDOW_SCALE;

  p2 -= getViewPortOffset();
  p2 *= WINDOW_SCALE;

  if (blue) {
    SDL_SetRenderDrawColor(mRenderer, kBlueLineColor[0], kBlueLineColor[1], kBlueLineColor[2], kBlueLineColor[3]);
  } else {
    SDL_SetRenderDrawColor(mRenderer, kLineColor[0], kLineColor[1], kLineColor[2], kLineColor[3]);
  }
  SDL_RenderDrawLine(mRenderer, p1.x, p1.y, p2.x, p2.y);
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);
}

void Graphics::setViewPort(FloatPosition pos) {
  mViewPort = pos;
}

FloatPosition Graphics::getViewPortOffset() {
  return FloatPosition(mViewPort.x - SCREEN_WIDTH / 2, mViewPort.y - SCREEN_HEIGHT / 2);
}


void Graphics::setTransitionAlphaMod(Uint8 alphaMod) {
  mTransitionAlphaMod = alphaMod;
}

void Graphics::drawWindowBorders() {
  SDL_SetRenderDrawColor(mRenderer, kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2], kBackgroundColor[3]);

  Size borderSize = ScreenProperties::getInstance().getBorderSize();
  Size windowSize = ScreenProperties::getInstance().getWindowSize();

  SDL_Rect rect;
  rect.x = rect.y = 0;
  rect.w = borderSize.w;
  rect.h = windowSize.h;
  SDL_RenderFillRect(mRenderer, &rect);

  rect.x = rect.y = 0;
  rect.w = windowSize.w;
  rect.h = borderSize.h;
  SDL_RenderFillRect(mRenderer, &rect);

  rect.x = windowSize.w - borderSize.w;
  rect.y = 0;
  rect.w = borderSize.w;
  rect.h = windowSize.h;
  SDL_RenderFillRect(mRenderer, &rect);

  rect.x = 0;
  rect.y = windowSize.h - borderSize.h;
  rect.w = windowSize.w;
  rect.h = borderSize.h;
  SDL_RenderFillRect(mRenderer, &rect);
}
