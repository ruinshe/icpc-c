#ifndef UNDIRECTED_BBC_H
#define UNDIRECTED_BBC_H

#ifndef BRIDGE_CODE
#define BRIDGE_CODE
#endif // BRIDGE_CODE

#include "graph.h"

edge_t *head[MaxN], *stack[MaxN];
int id[MaxN], low[MaxN], top, K;

void dfs(int u) {
  int v;
  id[u] = low[u] = ++K;
  for (edge_t* it = head[u]; it; it = it->next) {
    if (used[it->weight]) continue;
    v = it->to;
    stack[top++] = it;
    used[it->weight] = true;
    if (id[v] == 0) {
      dfs(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] >= id[u]) {
        edge_t* edge;
        edge_t* cur_edge = it;
        do {
          edge = stack[--top];
        } while (edge != cur_edge);
        if (low[v] > id[u]) {
          BRIDGE_CODE
        }
      }
    } else {
      low[u] = std::min(low[u], id[v]);
    }
  }
}

#endif // UNDIRECTED_BBC_H
