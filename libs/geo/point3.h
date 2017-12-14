#ifndef POINT3_H
#define POINT3_H

#include <cstdio>
#include <cmath>

struct point3_t {
  double x, y, z;
  point3_t() {}
  point3_t(double x, double y, double z) : x(x), y(y), z(z) {}
  point3_t operator+(const point3_t& p1) const { return point3_t(x + p1.x, y + p1.y, z + p1.z); }
  point3_t operator-(const point3_t& p1) const { return point3_t(x - p1.x, y - p1.y, z - p1.z); }
  point3_t operator*(const point3_t& p) const {
    return point3_t(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
  }
  point3_t operator*(const double& d) const { return point3_t(x * d, y * d, z * d); }
  point3_t operator/(const double& d) const { return point3_t(x / d, y / d, z / d); }
  point3_t operator-() const { return point3_t(-x, -y, -z); }
  double operator&(const point3_t& p) const { return x * p.x + y * p.y + z * p.z; }
  double norm() const { return sqrt(x * x + y * y + z * z); }
  void init() { scanf("%lf%lf%lf", &x, &y, &z); }
  void print() const { printf("(%.3f, %.3f, %.3f)", x, y, z); }
};

#endif
