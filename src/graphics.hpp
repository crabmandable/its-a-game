#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>
#include "geometry.hpp"
class Graphics {
  public:
    enum class RenderLayer: char {
      //charachters used to create texture keys for the mTextures map
      Background = 'b',
      Foreground = 'f'
    }; 

    struct DrawConfig {
      float paralaxX = 1;
      float paralaxY = 1;
      SDL_RendererFlip flip = SDL_FLIP_NONE;
      bool repeatX = false;
      bool repeatY = false;
    };

    static const int TILE_SIZE = 16;
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 360;
    static const int HEIGHT_RATIO = 9;
    static const int WIDTH_RATIO = 16;
    static const int OVERBUFFER = 2;
    const int kLineColor[4] = {255, 0, 0, SDL_ALPHA_OPAQUE};
    const int kBlueLineColor[4] = {0, 0, 255, SDL_ALPHA_OPAQUE};
    const int kBackgroundColor[4] = {20, 50, 128, SDL_ALPHA_OPAQUE};

    static std::string getResourcePath(const std::string &subDir = "");

    Graphics();
    ~Graphics();

    void init();
    void drawBackground(std::string path, SDL_Rect src, DrawConfig& config);
    void drawTexture(RenderLayer layer, std::string path, Rect src, Rect dest, DrawConfig& config);
    void drawTile(std::string tileSheetPath, Rect src, int columns, int row);
    void drawLine(Position p1, Position p2, bool blue = false);
    void overlayColor(Uint8* color);
    void beginDraw();
    void present();
    void blitForegroundToScreen();
    void setViewPort(FloatPosition pos);

  private:
    void draw(RenderLayer layer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, DrawConfig& config);
    SDL_Renderer* getRenderer(RenderLayer layer);
    SDL_Texture* getTexture(std::string path, RenderLayer layer);
    void updateWindowSize();
    FloatPosition getViewPortOffset();

    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    SDL_Surface* mForegroundSurface{nullptr};
    SDL_Renderer* mForegroundRenderer{nullptr};
    std::map<std::string, SDL_Texture*> mTextures;
    int mWindowHeight, mWindowWidth;
    float mWindowScale;

    FloatPosition mViewPort{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
};
#endif //GRAPHICS_H
