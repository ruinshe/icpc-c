#ifndef GRAPH_H
#define GRAPH_H

struct edge_t {
  int to, weight;
  edge_t *next;
} edges[MaxE], *cure;

inline void add_edge(edge_t **head, int u, int v, int weight = 0) {
  cure->to = v;
  cure->weight = weight;
  cure->next = head[u];
  head[u] = cure++;
}

#endif
