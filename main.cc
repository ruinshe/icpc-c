#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>

std::istream &in(std::cin);
std::ostream &out(std::cout);

const int MaxN = 1005;
const int MaxE = MaxN * 10;
const int MaxH = MaxN;
const double PI = acos(-1.0);
const double eps = 1e-8;

#include "libs/geo/geo.hpp"
#include "libs/geo/point.hpp"
#include "libs/geo/segment.hpp"
#include "libs/ds/heap.hpp"

point_t p[MaxN];
bool mp[MaxN][MaxN];
double dp[MaxN], c[MaxN];
double angle;
int n;

struct line_t : public segment_t {
  double ang;
  double beta, dis;

  line_t() { }

  line_t(const point_t &a, const point_t &b) : segment_t(a, b) {
    ang = ::ang(a);
    beta = acos((a & (a - b)) / a.norm() / (a - b).norm());
    dis = a.norm();
  }

  double get(const double &alpha) const {
    double sinA = sin(PI - alpha - beta + ang);
    return sgn(sinA) ? dis * sin(beta) / sinA : dis;
  }

  bool operator<(const line_t &other) {
    return sgn(get(angle) - other.get(angle)) < 0;
  }
};

struct event_t {
  line_t line;
  double ang;
  int id, fd;

  event_t() { }

  event_t(const line_t &line, const double &ang, int id, int fd)
      : line(line), ang(ang), id(id), fd(fd) {
  }

  bool operator<(const event_t &other) const {
    int fp = sgn(ang - other.ang);
    if (fp) return fp < 0;
    else return fd > other.fd;
  }
} events[MaxE];

heap_t<line_t> heap;

void solve() {
  int T, m;
  double lhs, rhs, in_ang, out_ang, ang;
  in >> T;
  for (int cas = 1; cas <= T; cas++) {
    in >> n;
    for (int i = 1; i <= n; i++) {
      in >> p[i].x >> p[i].y >> c[i];
      for (int j = i + 1; j <= n; j++) mp[i][j] = false;
    }
    p[0] = p[n];
    p[n + 1] = p[1];

    for (int i = 1; i < n; i++) {
      mp[i][i + 1] = true;
      if (i == n - 1) continue;
      lhs = ::ang(p[i + 1] - p[i]);
      rhs = ::ang(p[i - 1] - p[i]);
      heap.init(n);
      m = 0;
      for (int j = 1; j <= n; j++) {
        if (j + 1 == i || (j == n && i == 1)) continue;
        if (i == j) continue;
        line_t line = line_t(p[j] - p[i], p[j + 1] - p[i]);
        int rel = sgn(line.a * (line.b - line.a));
        if (rel == 0) continue;
        if (rel < 0) std::swap(line.a, line.b);
        ang = ::ang(p[j] - p[i]);
        in_ang = ::ang(line.a);
        out_ang = ::ang(line.b);
        if (in_ang < out_ang + eps) {
          events[m++] = event_t(line, in_ang, j, 1);
          events[m++] = event_t(line, out_ang, j, -1);
        } else {
          events[m++] = event_t(line, in_ang, j, 1);
          events[m++] = event_t(line, PI, j, -1);
          events[m++] = event_t(line, -PI, j, 1);
          events[m++] = event_t(line, out_ang, j, -1);
        }
        if (j > i + 1 && !(ang > lhs - eps && ang < rhs + eps)) {
          events[m++] = event_t(line, ang, j, 0);
        }
      }
      std::sort(events, events + m);
//        for (int j = 0; j < m; j++)
//          out << events[j].ang << " " << events[j].fd << " " << events[j].id
//          << " (" << p[events[j].id].x << ", "
//          << p[events[j].id].y << ")" << std::endl;
//        out << "===============" << std::endl;
      for (int j = 0; j < m; j++) {
        angle = events[j].ang;
        if (events[j].fd == 1) {
          heap.add(events[j].id, events[j].line);
        } else if (events[j].fd == -1) {
          heap.remove(events[j].id);
        } else {
          if (heap.d[heap.peek()].has(events[j].line.a)) {
            mp[i][events[j].id] = true;
          }
        }
      }
    }

//      for (int i = 1; i <= n; i++)
//        for (int j = i + 1; j <= n; j++)
//          if (mp[i][j])
//            out << "valid " << i << " " << j << std::endl;

    double res = c[1];
    std::fill(dp, dp + n + 1, -1e20);
    dp[1] = c[1];
    for (int i = 2; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        if (mp[j][i]) dp[i] = std::max(dp[i], dp[j] - distance(p[i], p[j]) + c[i]);
      }
      res = std::max(res, dp[i]);
    }
    out << "Case #" << cas << ": " << std::fixed << res << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  out.precision(16);
  solve();
  return 0;
}
