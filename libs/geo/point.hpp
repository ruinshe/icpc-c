#ifndef POINT_H
#define POINT_H

#include <math.h>

struct point_t {
  double x, y;

  point_t() { }

  point_t(double x, double y) : x(x), y(y) { }

  point_t operator+(const point_t &p) const { return point_t(x + p.x, y + p.y); }

  point_t operator-(const point_t &p) const { return point_t(x - p.x, y - p.y); }

  point_t operator*(const double &d) const { return point_t(x * d, y * d); }

  point_t operator/(const double &d) const { return point_t(x / d, y / d); }

  double operator*(const point_t &p) const { return x * p.y - y * p.x; }

  double operator&(const point_t &p) const { return x * p.x + y * p.y; }

  double norm() const { return hypot(y, x); }
};

inline double ang(const point_t &p) {
  return atan2(p.y, p.x);
}

inline double distance(const point_t &a, const point_t &b) {
  return (b - a).norm();
}

#endif
