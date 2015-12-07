#ifndef UNDIRECTED_BCC_H
#define UNDIRECTED_BCC_H

#include <algorithm>
#include "graph.hpp"

edge_t *undirected_head[MaxN];
bool used[MaxE], visited[MaxN], bridge[MaxE];
int id[MaxN], low[MaxN];
int K;

void bcc(int u) {
  int v;
  id[u] = low[u] = ++K;
  for (edge_t *iter = undirected_head[u]; iter; iter = iter->next) {
    v = iter->to;
    if (used[iter->weight]) continue;
    used[iter->weight] = true;
    if (!id[v]) {
      bcc(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] > id[u]) bridge[iter->weight] = true;
    } else {
      low[u] = std::min(low[u], id[v]);
    }
  }
}

#endif
