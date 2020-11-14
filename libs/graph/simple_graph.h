#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H

#include <cassert>

#ifndef MaxE
#define MaxE 10005
#endif

#ifndef MACRO_GRAPH_EXTRA_FIELDS
#define MACRO_GRAPH_EXTRA_FIELDS
#endif // MACRO_GRAPH_EXTRA_FIELDS

struct edge_t {
  int to;
  MACRO_GRAPH_EXTRA_FIELDS
  edge_t *next;

  struct iterator {
    edge_t *iter;
    iterator(edge_t *_iter) : iter(_iter) {}
    iterator &operator++(int) {
      assert(iter);
      iter = iter->next;
      return *this;
    }
    bool has_next() const { return iter != NULL; }
    edge_t &operator*() const { return *iter; }
    edge_t *operator->() const { return iter; }
  };

} edges[MaxE], *cure;

inline edge_t *add_edge(edge_t **head, int u, int v) {
  cure->to = v;
  cure->next = head[u];
  head[u] = cure;
  return cure++;
}

#define foreach(head, it) for (edge_t::iterator it = head; it.has_next(); it++)

#endif // SIMPLE_GRAPH_H
