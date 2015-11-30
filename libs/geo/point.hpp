#ifndef POINT_H
#define POINT_H

#include <math.h>

template<typename T = double>
struct point_t {
  T x, y;
  point_t() { }
  point_t(T x, T y) : x(x), y(y) { }
  point_t operator+(const point_t &p) const { return point_t(x + p.x, y + p.y); }
  point_t operator-(const point_t &p) const { return point_t(x - p.x, y - p.y); }
  point_t operator*(const double &d) const { return point_t(x * d, y * d); }
  point_t operator/(const double &d) const { return point_t(x / d, y / d); }
  T operator*(const point_t &p) const { return x * p.y - y * p.x; }
  T operator&(const point_t &p) const { return x * p.x + y * p.y; }
  double norm() const { return hypot(y, x); }
  int getId() const {
    if (y == 0) return x > 0 ? 0 : 2;
    else return y > 0 ? 1 : 3;
  }
};

template<typename T>
inline double ang(const point_t<T> &p) {
  return atan2(p.y, p.x);
}

template<typename T>
inline double distance(const point_t<T> &a, const point_t<T> &b) {
  return (b - a).norm();
}

#endif
