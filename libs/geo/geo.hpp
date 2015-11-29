#ifndef GEO_H
#define GEO_H

inline int sgn(double x) {
  return x < -eps ? -1 : x > eps;
}

#endif
