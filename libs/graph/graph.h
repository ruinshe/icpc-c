#ifndef GRAPH_H
#define GRAPH_H

#ifndef MACRO_GRAPH_EXTRA_FIELDS
#define MACRO_GRAPH_EXTRA_FIELDS int weight;
#endif

#include "simple_graph.h"

inline void add_edge(edge_t** head, int u, int v, int weight) {
  cure->to = v;
  cure->weight = weight;
  cure->next = head[u];
  head[u] = cure++;
}

#endif
