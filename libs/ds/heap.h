#ifndef HEAP_H
#define HEAP_H

#ifndef MaxH
#define MaxH 1005
#endif

#include <algorithm>

template<typename T>
struct heap_t {
  int h[MaxH], pos[MaxH];
  T d[MaxH];
  int n;

  inline void init(int maxId) {
    n = 0;
    for (int i = 0; i <= maxId; i++) pos[i] = -1;
  }

  inline T top() {
    return d[h[1]];
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

  inline void add(int k, T v) {
    if (pos[k] == -1) h[pos[k] = ++n] = k;
    d[k] = v;
    sink(pos[k]);
    swin(pos[k]);
  }

  inline void remove(int k) {
    if (pos[k] == -1) return;
    int p = pos[k];
    pos[k] = -1;
    h[p] = h[n];
    if (p != n--) {
      pos[h[p]] = p;
      sink(p);
      swin(p);
    }
  }

  bool empty() {
    return n == 0;
  }
};

#endif
