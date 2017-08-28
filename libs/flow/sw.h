#ifndef SW_H
#define SW_H

#include <limits>

int flow[MaxN][MaxN], distance[MaxN];
bool visited[MaxN], closed[MaxN];

int prim(int n, int maxId, int &s, int &t) {
  int res = 0;
  s = t = 0;
  std::fill(visited, visited + n + 1, false);
  std::fill(distance, distance + n + 1, 0);
  for (int i = 1; i <= maxId; i++) {
    int idx = 0, max = std::numeric_limits<int>::min();
    for (int j = 1; j <= n; j++) {
      if (!closed[j] && !visited[j] && distance[j] > max) {
        max = distance[j];
        idx = j;
      }
    }
    visited[idx] = true;
    s = t;
    t = idx;
    res = distance[t];
    for (int j = 1; j <= n; j++) {
      if (!closed[j] && !visited[j]) distance[j] += flow[idx][j];
    }
  }
  return res;
}

int stoer(int n) {
  int res = std::numeric_limits<int>::max(), s, t;
  std::fill(closed, closed + n + 1, false);
  for (int i = 0; i < n - 1; i++) {
    res = std::min(res, prim(n, n - i, s, t));
    closed[t] = true;
    for (int j = 1; j <= n; j++) {
      if (!closed[j]) {
        flow[j][s] += flow[j][t];
        flow[s][j] += flow[t][j];
      }
    }
  }
  return res;
}

#endif
