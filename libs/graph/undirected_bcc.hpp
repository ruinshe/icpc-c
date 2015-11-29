#ifndef UNDIRECTED_BCC_H
#define UNDIRECTED_BCC_H

#include <algorithm>
#include "graph.hpp"

edge_t *undirected_head[MaxN];
bool used[MaxE], visited[MaxN], bridge[MaxE];
int id[MaxN], distance[MaxN];
int K;

void bcc(int u) {
  int v;
  id[u] = distance[u] = ++K;
  for (edge_t *iter = undirected_head[u]; iter; iter = iter->next) {
    v = iter->to;
    if (used[iter->weight]) continue;
    used[iter->weight] = true;
    if (!id[v]) {
      bcc(v);
      distance[u] = std::min(distance[u], distance[v]);
      if (distance[v] > id[u]) bridge[iter->weight] = true;
    } else {
      distance[u] = std::min(distance[u], id[v]);
    }
  }
}

#endif
