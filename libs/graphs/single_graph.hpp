#ifndef GRAPH_H
#define GRAPH_H

struct edge_t {
  int to;
  edge_t* next;
} edges[MaxE], *cure;

inline void add_edge(edge_t** head, int u, int v) {
  cure->to = v;
  cure->next = head[u];
  head[u] = cure++;
}

#endif
