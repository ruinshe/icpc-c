#ifndef GEO_H
#define GEO_H

inline int sgn(double x) {
  return x < -eps ? -1 : x > eps;
}

inline int sgn(int x) {
  return x < 0 ? -1 : x > 0;
}

inline int sgn(long long x) {
  return x < 0 ? -1 : x > 0;
}

#endif
