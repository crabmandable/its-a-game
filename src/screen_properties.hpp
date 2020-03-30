#ifndef _SCREEN_PROPERTIES_HPP_
#define _SCREEN_PROPERTIES_HPP_
#include <vector>
#include <float.h>

#include "geometry.hpp"

#define SCREEN_WIDTH ScreenProperties::getInstance().getScreenSize().w
#define SCREEN_HEIGHT ScreenProperties::getInstance().getScreenSize().h
#define WINDOW_SCALE ScreenProperties::getInstance().getWindowScale()

class ScreenProperties
{
  public:
    const std::vector<Size> kSupportedAspectRatios = {{16, 9}, {16, 10}, {4, 3}};
    static const int TARGET_WIDTH = 640;

    static const int DEFAULT_WIDTH = TARGET_WIDTH;
    static const int DEFAULT_HEIGHT = 480;

    static ScreenProperties& getInstance();

    Size getScreenSize();
    void setScreenSize(Size windowSize);
    float getWindowScale();
    Size getWindowSize();
    Size getBorderSize();

  private:
    Size mWindowSize;
    Size mScreenSize{DEFAULT_WIDTH, DEFAULT_HEIGHT};
    Size mScreenRatio{16, 9};
    float mWindowScale = 1.0;
    ScreenProperties() {}
    float getClosestSupportedAspectRatio(float windowAspect);

  public:
    ScreenProperties(ScreenProperties const&) = delete;
    void operator=(ScreenProperties const&) = delete;
};
#endif //_SCREEN_PROPERTIES_HPP_
