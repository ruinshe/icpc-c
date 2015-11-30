#ifndef SEGMENT_H
#define SEGMENT_H

#include "geo.hpp"
#include "point.hpp"

template<typename T>
struct segment_t {
  point_t<T> a, b;
  segment_t() { }
  segment_t(const point_t<T> &a, const point_t<T> &b) : a(a), b(b) { }
  bool has(const point_t<T> &p) const {
    return sgn((p - a) * (b - a)) == 0
           && sgn(p.x - a.x) * sgn(p.x - b.x) <= 0
           && sgn(p.y - a.y) * sgn(p.y - b.y) <= 0;
  }
};

#endif
