#ifndef GRAPH_H
#define GRAPH_H

#define MACRO_GRAPH_EXTRA_FIELDS int weight;

#include "simple_graph.hpp"

inline void add_edge(edge_t** head, int u, int v, int weight) {
  cure->to = v;
  cure->weight = weight;
  cure->next = head[u];
  head[u] = cure++;
}

#endif
