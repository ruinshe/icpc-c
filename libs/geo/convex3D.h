#ifndef CONVEX_3D_H
#define CONVEX_3D_H

#include "point3.h"

#ifndef MaxN
#define MaxN 305
#endif

struct convex_t {
  struct face_t { int a, b, c; bool is_final_face; };
  int n;
  point3_t points[MaxN];
  int cnt;
  face_t faces[MaxN * 4];
  int to[MaxN][MaxN];
  double area(const point3_t& a, const point3_t& b, const point3_t& c) {
    return ((b - a) * (c - a)).norm();
  }
  double volume(const point3_t& a, const point3_t& b, const point3_t& c, const point3_t& d) {
    return ((b - a) * (c - a)) & (d - a); 
  }
  double point_to_face(const point3_t& p, const face_t& f) {
    point3_t m = points[f.b] - points[f.a], n = points[f.c] - points[f.a], t = p - points[f.a];
    return (m * n) & t;
  }
  void solveOne(const int p, const int a, const int b) {
    int f = to[a][b];
    face_t add;
    if (faces[f].is_final_face) {
      if (point_to_face(points[p], faces[f]) > eps) dfs(p, f);
      else {
        add.a = b, add.b = a, add.c = p, add.is_final_face = true;
        to[p][b] = to[a][p] = to[b][a] = cnt;
        faces[cnt++] = add;
      }
    }
  }
  void dfs(const int p, const int cur) {
    faces[cur].is_final_face = false;
    solveOne(p, faces[cur].b, faces[cur].a);
    solveOne(p, faces[cur].c, faces[cur].b);
    solveOne(p, faces[cur].a, faces[cur].c);
  }
  bool same(const int s, const int t) {
    point3_t &a = points[faces[s].a], &b = points[faces[s].b], &c = points[faces[s].c];
    return fabs(volume(a, b, c, points[faces[t].a])) < eps
                                                       && fabs(volume(a, b, c, points[faces[t].b])) < eps
                                                                                                      && fabs(volume(a, b, c, points[faces[t].c])) < eps;
  }
  void solve() {
    if (n < 4) return;

    for (int i = 2; i < n; i++) {
      if (sgn(((points[0] - points[1]) * (points[1] - points[i])).norm())) {
        std::swap(points[2], points[i]);
        break;
      }
    }
    for (int i = 3; i < n; i++) {
      if (sgn(((points[0] - points[1]) * (points[1] - points[2])) & (points[0] - points[i]))) {
        std::swap(points[3], points[i]);
        break;
      }
    }

    shuffle(points + 4, points + n, std::default_random_engine());

    cnt = 0;
    face_t add;
    for (int i = 0; i < 4; i++) {
      add.a = (i + 1) % 4, add.b = (i + 2) % 4, add.c = (i + 3) % 4, add.is_final_face = true;
      if (point_to_face(points[i], add) > 0) std::swap(add.b, add.c);
      to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
      faces[cnt++] = add;
    }

    for (int i = 4; i < n; i++) {
      for (int j = 0; j < cnt; j++) {
        if (faces[j].is_final_face && point_to_face(points[i], faces[j]) > eps) {
          dfs(i, j);
          break;
        }
      }
    }

    int tmp = cnt;
    cnt = 0;
    for (int i = 0; i < tmp; i++) {
      if (faces[i].is_final_face) faces[cnt++] = faces[i];
    }
  }
  double area() {
    double res = 0.0;
    for (int i = 0; i < cnt; i++) {
      res += area(points[faces[i].a], points[faces[i].b], points[faces[i].c]);
    }
    return res / 2.0;
  }
  double volume() {
    point3_t O(0, 0, 0);
    double res = 0.0;
    for (int i = 0; i < cnt; i++) {
      res += volume(O, points[faces[i].a], points[faces[i].b], points[faces[i].c]);
    }
    return fabs(res / 6.0);
  }
  int face_cnt_tri() { return cnt; }
  int face_cnt() {
    int res = 0;
    for (int i = 0; i < cnt; i++) {
      bool ok = true;
      for (int j = 0; j < i; j++) {
        if (same(i, j)) {
          ok = false;
          break;
        }
      }
      res += ok;
    }
    return res;
  }
};

#endif
