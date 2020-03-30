#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>
#include "geometry.hpp"
#include "screen_properties.hpp"

class Graphics {
  public:
    enum class RenderLayer: char {
      //charachters used to create texture keys for the mTextures map
      Background = 'b',
      Foreground = 'f',
      Transition = 't'
    }; 

    struct DrawConfig {
      float paralaxX = 1;
      float paralaxY = 1;
      SDL_RendererFlip flip = SDL_FLIP_NONE;
      bool repeatX = false;
      bool repeatY = false;
    };

    static const int TILE_SIZE = 16;
    // OVERBUFFER is used for foreground layer, in order to do sub-pixel camera movements
    static const int OVERBUFFER = 2;
    const Uint8 kLineColor[4] = {255, 0, 0, SDL_ALPHA_OPAQUE};
    const Uint8 kBlueLineColor[4] = {0, 0, 255, SDL_ALPHA_OPAQUE};
    const Uint8 kBackgroundColor[4] = {0, 0, 0, SDL_ALPHA_OPAQUE};

    static std::string getResourcePath(const std::string &subDir = "");

    Graphics();
    ~Graphics();

    void init();
    void drawBackground(std::string path, SDL_Rect src, DrawConfig& config);
    void drawTexture(RenderLayer layer, std::string path, Rect src, Rect dest, DrawConfig& config);
    void drawTile(std::string tileSheetPath, Rect src, int columns, int row);
    void drawLine(Position p1, Position p2, bool blue = false);
    void drawWindowBorders();
    void overlayColor(Uint8* color);
    void beginDraw();
    void blitLayersToScreen();
    void present();
    void setViewPort(FloatPosition pos);
    SDL_Renderer* getRenderer(RenderLayer layer);
    void setTransitionAlphaMod(Uint8 alphaMod);

  private:
    // scale up a render surface and blit it to the screen
    void blitSurfaceToScreen(SDL_Surface* surface, Uint8 alphaMod = 0xFF);
    // scale up foreground and blit it to the screen, compensating for view port rounding
    void blitForegroundToScreen();
    void draw(RenderLayer layer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, DrawConfig& config);
    SDL_Texture* getTexture(std::string path, RenderLayer layer);
    void updateWindowSize();
    FloatPosition getViewPortOffset();

    const Size kBufferSize = {640, 480};

    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    SDL_Surface* mForegroundSurface{nullptr};
    SDL_Renderer* mForegroundRenderer{nullptr};
    SDL_Surface* mTransitionSurface{nullptr};
    SDL_Renderer* mTransitionRenderer{nullptr};
    std::map<std::string, SDL_Texture*> mTextures;

    FloatPosition mViewPort{ScreenProperties::DEFAULT_WIDTH / 2, ScreenProperties::DEFAULT_HEIGHT / 2};

    Uint8 mTransitionAlphaMod = 0xFF;
};
#endif //GRAPHICS_H
