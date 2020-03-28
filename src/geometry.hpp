#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <SDL2/SDL.h>
#include <algorithm>

template <class Type, class InteroperableType>
class Point {
  public:
    Type x = 0;
    Type y = 0;
    Point() {};
    Point(Type x_, Type y_) {
      x = x_;
      y = y_;
    };

    Point<Type, InteroperableType>(Point<InteroperableType, Type> p2) {
      x = p2.x;
      y = p2.y;
    }

    Point operator-() {
      return Point(-x, -y);
    }

    Point& operator*=(float c) {
      x *= c;
      y *= c;
      return *this;
    }

    Point operator/(const int rhs) {
      return Point(x / rhs, y / rhs);
    }

    Point operator-(const int rhs) {
      return Point(x - rhs, y - rhs);
    }

    friend Point operator*(Point lhs, const float rhs) {
      return Point(lhs.x * rhs, lhs.y * rhs);
    }

    Point& operator*=(int c) {
      x *= c;
      y *= c;
    }

    friend Point& operator+=(Point& lhs, Point rhs) {
      lhs.x += rhs.x;
      lhs.y += rhs.y;
      return lhs;
    }
    
    friend Point& operator-=(Point& lhs, Point rhs) {
      lhs.x -= rhs.x;
      lhs.y -= rhs.y;
      return lhs;
    }

    friend Point<Type, InteroperableType>& operator+=(Point<Type, InteroperableType>& lhs, Point<InteroperableType, Type> rhs) {
      lhs.x += rhs.x;
      lhs.y += rhs.y;
      return lhs;
    }

    friend Point operator*(Point lhs, Point rhs) {
      return Point(lhs.x * rhs.x, lhs.y * rhs.y);
    }

    friend Point operator+(Point lhs, Point rhs) {
      return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend Point operator-(Point lhs, Point rhs) {
      return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    Point absolute() {
      return Point(abs(x), std::abs(y));
    }

    bool isZero() {
      return x == 0 && y == 0;
    }

    static Point min(Point a, Point b) {
      return Point(std::min(a.x, b.x), std::min(a.y, b.y));
    }

    static Point max(Point a, Point b) {
      return Point(std::max(a.x, b.x), std::max(a.y, b.y));
    }

    static Point max(float c, Point p) {
      return Point(std::max(c, p.x), std::max(c, p.y));
    }

    static Point max(int c, Point p) {
      return Point(std::max(c, p.x), std::max(c, p.y));
    }
};

typedef Point<int, float> Position;
typedef Point<int, float> Vector2D;
typedef Point<float, int> FloatPosition;
typedef Point<float, int> Velocity;
typedef Point<float, int> Acceleration;

class Size {
  public:
    int w = 0;
    int h = 0;

    Size() {};
    Size(int width, int height) {
      w = width;
      h = height;
    };

    Size operator*(int c) {
      return Size(w * c, h * c);
    }
};

struct Rect {
  Position origin;
  Size size;

  Rect() {};

  Rect(Position o, Size s) {
    origin = o;
    size = s;
  }

  SDL_Rect toSDLRect() {
    SDL_Rect r;
    r.x = origin.x;
    r.y = origin.y;
    r.w = size.w;
    r.h = size.h;

    return  r;
  }

  Rect& operator=(SDL_Rect& r) {
    origin.x = r.x;
    origin.y = r.y;
    size.w = r.w;
    size.h = r.h;

    return *this;
  }

  operator SDL_Rect() const {
    SDL_Rect r;
    r.x = origin.x;
    r.y = origin.y;
    r.w = size.w;
    r.h = size.h;
    return r;
  }


  static Rect fromSDLRect(SDL_Rect& sdlRect) {
    return Rect({sdlRect.x, sdlRect.y}, {sdlRect.w, sdlRect.h});
  }

  bool containsPoint(Position p) {
    return p.x >= origin.x && p.x <= origin.x + size.w
      && p.y >= origin.y && p.y <= origin.y + size.h;
  }
};

#endif //_UTILS_HPP_
