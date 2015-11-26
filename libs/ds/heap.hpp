#ifndef HEAP_H
#define HEAP_H

#include <algorithm>

struct heap_t {
  int h[MaxH], pos[MaxH];
  int n;

  inline void init() {
    n = 0;
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
      if (lhs <= n && comp(h[lhs], h[idx])) idx = lhs;
      if (rhs <= n && comp(h[rhs], h[idx])) idx = rhs;
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
      if (comp(h[k], h[p])) {
        std::swap(h[k], h[p]);
        pos[h[k]] = k;
        pos[h[p]] = p;
        k = p;
      } else {
        break;
      }
    }
  }

  inline void add(int k) {
    h[++n] = k;
    pos[k] = n;
    swin(n);
  }
} heap;

#endif
