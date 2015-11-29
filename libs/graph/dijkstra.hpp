#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <vector>
#include <functional>
#include "graph.hpp"

const int MaxH = MaxN;

#include "../ds/heap.hpp"

void dijkstra(int s, int n, edge_t **head, long long *distance, int *pre = NULL) {
  static heap_t<long long> heap;
  for (int i = 1; i <= n; i++) distance[i] = 0x3F3F3F3F3F3F3F3FLL;
  int u, v;
  heap.init(n);
  heap.add(s, 0);
  distance[s] = 0;
  while (!heap.empty()) {
    u = heap.peek();
    for (edge_t *iter = head[u]; iter; iter = iter->next) {
      v = iter->to;
      if (distance[v] - distance[u] > iter->weight) {
        distance[v] = distance[u] + iter->weight;
        if (pre) pre[v] = u;
        heap.add(v, distance[v]);
      }
    }
  }
}

#endif
