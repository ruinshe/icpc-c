#ifndef KM_T
#define KM_T

#define foreach(e,x) for(__typeof((x).begin()) e=(x).begin(); e!=(x).end(); ++e)

int w[MaxN][MaxN];
int x[MaxN], y[MaxN], px[MaxN], py[MaxN], sy[MaxN], sy[MaxN], slack[MaxN];
int par[MaxN];
int n;
int pa[MaxN][2], pb[MaxN][2], n0, m0, na, nb;
char s[MaxN][MaxN];

inline void adjust(const int& v) {
  sy[v] = py[v];
  if (px[sy[v]] != -2) adjust(px[sy[v]]);
}

bool dfs(int v) {
  for (int i = 0; i < n; i++) {
    if (py[i] == -1) {
      if (slack[i] > x[v] + y[i] - w[v][i]) slack[i] = x[v] + y[i] - w[v][i], par[i] = v;
      if (x[v] + y[i] == w[v][i]) {
        py[i] = v;
        if (sy[i] == -1) {
          adjust(i);
          return 1;
        }
        if (px[sy[i]] != -1) continue;
        px[sy[i]] = i;
        if (find(sy[i])) return true;
      }
    }
  }
  return 0;
}

int km(int bar) {
  int i, j, m;
  bool ok;
  for (i = 0; i < n; i++) sy[i] = -1, y[i] = 0;
  for (i = 0; i < n; i++) {
    x[i] = 0;
    for (j = 0; j < n; j++) x[i] = std::max(x[i], w[i][j]);
    bar -= x[i];
  }
  if (bar >= 0) return 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) px[j] = py[j] = -1, slack[j] = oo;
    px[i] = -2;
    if (dfs(i)) continue;
    ok = false;
    while (!ok) {
      m = INF;
      for (j = 0; j < n; j++) if (py[j] == -1) m = fastMin(m, slack[j]);
      for (j = 0; j < n; j++) {
        if (px[j] != -1) {
          x[j] -= m;
          bar += m;
        }
        if (py[j] != -1) {
          y[j] += m;
          bar -= m;
        } else slack[j] -= m;
      }
      if (bar >= 0) return 0;
      for (j = 0; j < n; j++) {
        if (py[j] == -1 && !slack[j]) {
          py[j] = par[j];
          if (sy[j] == -1) {
            adjust(j);
            ok = true;
            break;
          }
          px[sy[j]] = j;
          if (dfs(sy[j])) {
            ok = true;
            break;
          }
        }
      }
    }
  }
  int res = 0;
  for (i = 0; i < n; i++) res += w[sy[i]][i];
  return res;
}

#endif
