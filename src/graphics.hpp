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

    static std::string getTexturePath(const std::string &subDir = "");

    Graphics();
    ~Graphics();

    void init();
    void destroyTexture(std::string path);
    void loadTexture(std::string path);
    void drawTexture(std::string path, SDL_Rect& src, SDL_Rect& dest);
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
