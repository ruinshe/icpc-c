#ifndef NUMERIC_H
#define NUMERIC_H

template<typename T>
inline void checkmin(T& a, const T& b) {
  if (a > b) a = b;
}

template<typename T>
inline void checkmax(T& a, const T& b) {
  if (a < b) a = b;
}

template<typename T>
inline T sqr(const T& x) {
  return x * x;
}

#endif  // NUMERIC_H
