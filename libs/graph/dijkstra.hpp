#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <vector>
#include <functional>
#include "graph.hpp"

std::priority_queue<
    std::pair<long long, int>,
    std::vector<std::pair<long long, int> >,
    std::greater<std::pair<long long, int> > > queue;

void dijkstra(int s, int n, edge_t **head, long long *distance) {
  for (int i = 1; i <= n; i++) distance[i] = 0x3F3F3F3F3F3F3F3FLL;
  int u, v;
  queue.push({0, s});
  distance[s] = 0;
  while (!queue.empty()) {
    const auto value = queue.top();
    queue.pop();
    if (distance[value.second] != value.first) continue;
    u = value.second;
    for (edge_t *iter = head[u]; iter; iter = iter->next) {
      v = iter->to;
      if (distance[v] - distance[u] > iter->weight) {
        distance[v] = distance[u] + iter->weight;
        queue.push({distance[v], v});
      }
    }
  }
}

#endif
