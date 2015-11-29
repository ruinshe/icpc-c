#ifndef SAP_H
#define SAP_H

namespace __sap {
  struct edge_t {
    int v, cap;
    edge_t *next, *rev;
  } edges[MaxE], *cur, *head[MaxN], *cure[MaxN], *pree[MaxN];
  int dist[MaxN], low[MaxN], gap[MaxN], pre[MaxN];
  int n, s, t;

  inline void add_edge(from, to, ccap, rcap) {
    cur->v = to;
    cur->cap = ccap;
    cur->next = head[from];
    cur->rev = cur + 1;
    head[from] = cur++;
    cur->v = from;
    cur->cap = rcap;
    cur->next = head[to];
    cur->rev = cur - 1;
    head[to] = cur++;
  }

  inline int sap() {
    int res = 0;
    bool done;

    for (int i = 0; i < n; i++) dist[i] = gap[i] = 0;
    gap[0] = n;
    int u = s;
    low[s] = INF;
    while (dist[s] < n) {
      done = true;
      for (edge_t *iter = cure[u]; iter; iter = iter->next) {
        int v = iter->v;
        cure[u] = iter;
        if (iter->cap && dist[u] == dist[v] + 1) {
          pre[v] = u;
          pree[v] = iter;
          low[v] = min(low[u], iter->cap);
          u = v;
          if (u == t) {
            do {
              pree[u]->cap -= low[t];
              pree[u]->rev->cap += low[t];
              u = pre[u];
            } while (u != s);
            res += low[t];
          }
          done = false;
          break;
        }
      }
      if (done) {
        if (!--gap[dist[u]]) return res;
        dist[u] = n;
        for (edge_t *iter = head[u]; iter; iter = iter->next) {
          if (iter->cap) {
            int v = iter->v;
            dist[u] = min(dist[u], dist[v] + 1);
          }
        }
        gap[dist[u]]++;
        cure[u] = head[u];
        if (u != s) {
          u = pre[u];
        }
      }
    }

    return res;
  }
}

#endif
