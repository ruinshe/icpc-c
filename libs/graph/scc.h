#ifndef SCC_H
#define SCC_H

#include "simple_graph.h"

#ifndef MaxN
#define MaxN 10005
#endif

edge_t *head[MaxN];
int low[MaxN], id[MaxN], visited[MaxN], stack[MaxN], top;
int bel[MaxN], nbel, nc;

void scc_init(int n) {
  std::fill(visited, visited + n, 0);
  std::fill(id, id + n, 0);
  top = nbel = nc = 0;
}

void dfs(int u) {
  stack[top++] = u;
  low[u] = id[u] = ++nc;
  visited[u] = 1;

  foreach (head[u], it) {
    int v = it->to;

    if (id[v] == 0) {
      dfs(v);
      if (low[u] > low[v]) {
        low[u] = low[v];
      }
    } else if (visited[v] > 0 && id[v] < low[u]) {
      low[u] = id[v];
    }
  }

  if (low[u] == id[u]) {
    int v;
    ++nbel;
    do {
      v = stack[--top];
      visited[v] = -1;
      bel[v] = nbel;
    } while (v != u);
  }
}

void tarjan(int n) {
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i);
    }
  }
}

#endif // SCC_H
