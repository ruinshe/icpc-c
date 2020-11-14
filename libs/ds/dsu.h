#ifndef DSU_H
#define DSU_H

#ifndef MaxN
#define MaxN 1005
#endif

struct dsu_t {
  int f[MaxN];

  void init(int n = MaxN) {
    for (int i = 0; i < n; i++)
      f[i] = i;
  }

  int getf(int x) { return f[x] == x ? x : f[x] = getf(f[x]); }

  void merge_to_f(int x, int p) { f[getf(x)] = p; }

  void merge_any(int x, int y) {
    if (getf(x) != getf(y)) {
      merge_to_f(getf(x), getf(y));
    }
  }
};

#endif // DSU_H
