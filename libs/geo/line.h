#ifndef LINE_H
#define LINE_H

template<typename T>
struct line_t {
  point_t<T> a, b;
  double k, c;
  line_t() { }
  line_t(const point_t<T> &a, const point_t<T> &b) : a(a), b(b) { }
  bool operator<(const line_t &other) const {
    int fd = sgn(k - other.k);
    if (fd) return fd < 0;
    else return sgn(c - other.c) < 0;
  }
  void set() {
    k = atan2(b.y - a.y, b.x - a.x);
    if (sgn(a.x - b.x)) c = (a * b) / fabs(a.x - b.x);
    else c = (a * b) / fabs(a.y - b.y);
  }
};

template<typename T>
bool line_ins(const line_t<T> &lhs, const line_t<T> &rhs) {
  return sgn((lhs.b - lhs.a) * (rhs.b - rhs.a)) != 0;
}

point_t<double> ins_point(const line_t<double> &lhs, const line_t<double> &rhs) {
  double u = (lhs.b - lhs.a) * (rhs.a - lhs.a);
  double v = (lhs.a - lhs.b) * (rhs.b - lhs.b);
  return (rhs.a * v + rhs.b * u) / (u + v);
}

#endif
