#include "screen_properties.hpp"

Size ScreenProperties::getScreenSize() {
  return mScreenSize;
}

float ScreenProperties::getWindowScale() {
  return mWindowScale;
}

void ScreenProperties::setScreenSize(Size windowSize) {
  mWindowSize = windowSize;
  float aspectRatio = getClosestSupportedAspectRatio((float)windowSize.w / windowSize.h);
  int height = TARGET_WIDTH / aspectRatio;
  mScreenSize = Size(TARGET_WIDTH, height);

  if (windowSize.w / mScreenRatio.w > windowSize.h / mScreenRatio.h) {
    mWindowScale = (float) windowSize.h / mScreenSize.h;
  } else {
    mWindowScale  = (float) windowSize.w / mScreenSize.w;
  }
}

Size ScreenProperties::getBorderSize() {
  return Size(
      ceil(abs(mWindowSize.w - (mScreenSize.w * mWindowScale)) / 2.0),
      ceil(abs(mWindowSize.h - (mScreenSize.h * mWindowScale)) / 2.0)
  );
}

Size ScreenProperties::getWindowSize() {
  return mWindowSize;
}

ScreenProperties& ScreenProperties::getInstance()
{
  static ScreenProperties instance;
  return instance;
}

float ScreenProperties::getClosestSupportedAspectRatio(float windowAspect) {
  float minDiff = FLT_MAX;
  float closestAspect = kSupportedAspectRatios[0].w / kSupportedAspectRatios[0].h;

  for (auto a : kSupportedAspectRatios) {
    float aspect = ((float)a.w / a.h);
    float diff = abs(windowAspect - aspect);
    if (minDiff > diff) {
      minDiff = diff;
      closestAspect = aspect;
    }
  }

  return closestAspect;
}
