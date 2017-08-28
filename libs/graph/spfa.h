#ifndef SPFA_H
#define SPFA_H

#include "graph.h"

void spfa(int s, int n, edge_t **head, long long *distance) {
  static int queue[MaxN];
  static bool visited[MaxN];
  int f = 0, b = 0, u, v;
  for (int i = 1; i <= n; i++) {
    distance[i] = 0x3F3F3F3F3F3F3F3FLL;
    visited[i] = false;
  }
  distance[s] = 0;
  queue[b++] = s;
  while (f != b) {
    u = queue[f++];
    if (f == MaxN) f = 0;
    visited[u] = false;
    for (edge_t *iter = head[u]; iter; iter = iter->next) {
      v = iter->to;
      if (distance[v] - distance[u] > iter->weight) {
        distance[v] = distance[u] + iter->weight;
        if (!visited[v]) {
          queue[b++] = v;
          if (b == MaxN) b = 0;
          visited[v] = true;
        }
      }
    }
  }
}

#endif
