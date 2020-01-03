#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>
class Graphics {
  public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 360;
    static const int HEIGHT_RATIO = 9;
    static const int WIDTH_RATIO = 16;
    const int kLineColor[4] = {255, 0, 0, SDL_ALPHA_OPAQUE};
    const int kBlueLineColor[4] = {0, 0, 255, SDL_ALPHA_OPAQUE};
    const int kBackgroundColor[4] = {0, 0, 0, SDL_ALPHA_OPAQUE};

    static std::string getResourcePath(const std::string &subDir = "");

    Graphics();
    ~Graphics();

    void init();
    void destroyTexture(std::string path);
    void loadTexture(std::string path);
    void drawTexture(std::string path, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawLine(int x1, int y1, int x2, int y2, bool blue = false);
    void beginDraw();
    void present();

  private:
    void updateWindowSize();

    SDL_Window* mWindow{nullptr};
    SDL_Renderer* mRenderer{nullptr};
    std::map<std::string, SDL_Texture*> mTextures;
    int mWindowHeight, mWindowWidth;
    float mWindowScale;
};
#endif //GRAPHICS_H
