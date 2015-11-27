#ifndef HEAP_H
#define HEAP_H

#include <algorithm>

struct heap_t {
  int h[MaxH], d[MaxH], pos[MaxH];
  int n;

  inline void init(int maxId) {
    n = 0;
    for (int i = 0; i <= maxId; i++) pos[i] = -1;
  }

  inline int poll() {
    return h[1];
  }

  inline int peek() {
    int res = h[1];
    pos[h[1]] = -1;
    h[1] = h[n--];
    if (n) {
      pos[h[1]] = 1;
      sink(1);
    }
    return res;
  }

  inline void sink(int k) {
    while (k <= n) {
      int idx = k, lhs = k << 1, rhs = k << 1 | 1;
      if (lhs <= n && d[h[lhs]] < d[h[idx]]) idx = lhs;
      if (rhs <= n && d[h[rhs]] < d[h[idx]]) idx = rhs;
      if (idx == k) break;
      else {
        std::swap(h[idx], h[k]);
        pos[h[idx]] = idx;
        pos[h[k]] = k;
        k = idx;
      }
    }
  }

  inline void swin(int k) {
    while (k > 1) {
      int p = k >> 1;
      if (d[h[k]] < d[h[p]]) {
        std::swap(h[k], h[p]);
        pos[h[k]] = k;
        pos[h[p]] = p;
        k = p;
      } else {
        break;
      }
    }
  }

  inline void add(int k, int v) {
    if (pos[k] == -1) {
      h[++n] = k;
      pos[k] = n;
    }
    d[k] = v;
    sink(pos[k]);
    swin(pos[k]);
  }
};

#endif
