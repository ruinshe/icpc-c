#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <vector>
#include <functional>
#include "graph.h"

const int MaxH = MaxN;

#include "../ds/heap.h"

void dijkstra(int s, int n, edge_t **head, long long *distance, int destination, int *pre = NULL) {
  static heap_t<long long> heap;
  for (int i = 0; i <= n; i++) distance[i] = INT64_INF;
  int u, v;
  heap.init(n);
  heap.add(s, 0);
  distance[s] = 0;
  while (!heap.empty()) {
    u = heap.peek();
    if (u == destination) return;
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
