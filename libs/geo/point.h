#ifndef POINT_H
#define POINT_H

template<typename T = double>
struct point_t {
  T x, y;
  point_t() { }
  point_t(T x, T y) : x(x), y(y) { }
  point_t<T> operator+(const point_t<T> &p) const { return point_t<T>(x + p.x, y + p.y); }
  point_t<T> operator-(const point_t<T> &p) const { return point_t<T>(x - p.x, y - p.y); }
  point_t<T> operator*(const double &d) const { return point_t<T>(x * d, y * d); }
  point_t<T> operator/(const double &d) const { return point_t<T>(x / d, y / d); }
  T operator*(const point_t<T> &p) const { return x * p.y - y * p.x; }
  T operator&(const point_t<T> &p) const { return x * p.x + y * p.y; }
  bool operator==(const point_t<T> &p) const { return sgn(x - p.x) == 0 && sgn(y - p.y) == 0; }
  double norm() const { return hypot(y, x); }
  int getId() const {
    if (y == 0) return x > 0 ? 0 : 2;
    else return y > 0 ? 1 : 3;
  }
};

template<typename T>
inline bool compPoly(const point_t<T>& lhs, const point_t<T>& rhs) {
  int fd = lhs.getId() - rhs.getId();
  if (fd) return fd < 0;
  else return lhs * rhs > 0;
}

template<typename T>
inline bool compCoord(const point_t<T>& lhs, const point_t<T>& rhs) {
  int fd = sgn(lhs.x - rhs.x);
  if (fd) return fd < 0;
  else return sgn(lhs.y - rhs.y) < 0;
}

template<typename T>
inline double ang(const point_t<T> &p) {
  return atan2(p.y, p.x);
}

template<typename T>
inline double distance(const point_t<T> &a, const point_t<T> &b) {
  return (b - a).norm();
}

template<typename T>
int xmult(const point_t<T> &p1, const point_t<T> &p2, const point_t<T> &p) {
  return sgn((p1 - p) * (p2 - p));
}

#endif
