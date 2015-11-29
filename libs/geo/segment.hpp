#ifndef SEGMENT_H
#define SEGMENT_H

#include "geo.hpp"
#include "point.hpp"

struct segment_t {
  point_t a, b;

  segment_t() { }

  segment_t(const point_t &a, const point_t &b) : a(a), b(b) { }

  bool has(const point_t &p) const {
    return sgn((p - a) * (b - a)) == 0
           && sgn(p.x - a.x) * sgn(p.x - b.x) <= 0
           && sgn(p.y - a.y) * sgn(p.y - b.y) <= 0;
  }
};

#endif
