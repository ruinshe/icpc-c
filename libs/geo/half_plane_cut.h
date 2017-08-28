#ifndef HALF_PLANE_CUT_H
#define HALF_PLANE_CUT_H

#include "line.h"

void half_plane_cut(line_t<double> *l, int n, point_t<double> *output, int &top) {
  int f, b;
  static line_t<double> queue[MaxN];
  top = 0;
  if (n < 3) return;

  b = 1;
  for (int i = 0; i < n; i++) l[i].set();
  std::sort(l, l + n);
  for (int i = 1; i < n; i++) if (sgn(l[i].k - l[i - 1].k)) l[b++] = l[i];

  n = b;
  f = b = 0;
  queue[b] = l[0];
  queue[++b] = l[1];
  for (int i = 2; i < n; i++) {
    if (!line_ins(queue[b], queue[b - 1]) || !line_ins(queue[f], queue[f + 1])) return;
    while (f != b && xmult(l[i].b, ins_point(queue[b], queue[b - 1]), l[i].a) < 0) b--;
    while (f != b && xmult(l[i].b, ins_point(queue[f], queue[f + 1]), l[i].a) < 0) f++;
    queue[++b] = l[i];
  }
  while (f != b && xmult(queue[f].b, ins_point(queue[b], queue[b - 1]), queue[f].a) < 0) b--;
  while (f != b && xmult(queue[b].b, ins_point(queue[f], queue[f + 1]), queue[b].a) < 0) f++;
  if (b <= f + 1) return;
  for (int i = f; i < b; i++) output[top++] = ins_point(queue[i], queue[i + 1]);
  if (f < b + 1) output[top++] = ins_point(queue[f], queue[b]);
  top = std::unique(output, output + top) - output;
  if (top && output[0] == output[top - 1]) top--;
}

#endif
