#ifndef SA_H
#define SA_H

int wa[MaxN], wb[MaxN], wv[MaxN], rank[MaxN], to[MaxN];

inline bool equals(int* y, int a, int b, int len) {
  return y[a] == y[b] && y[a + len] == y[b + len];
}

template<typename T>
void calc_sa(T *s, int *sa, int len, int charsize) {
  int *x = wa, *y = wb;

  std::fill(rank, rank + charsize + 1, 0);
  for (int i = 0; i < len; i++) rank[x[i] = s[i]]++;
  for (int i = 0; i < charsize; i++) rank[i + 1] += rank[i];
  for (int i = len - 1; i >= 0; i--) sa[--rank[x[i]]] = i;
  for (int j = 1, p = 1; p < len; j <<= 1, charsize = p) {
    for (p = 0; p < j; p++) y[p] = len - j + p;
    for (int i = 0; i < len; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
    for (int i = 0; i < len; i++) wv[i] = x[y[i]];
    std::fill(rank, rank + charsize + 1, 0);
    for (int i = 0; i < len; i++) rank[wv[i]]++;
    for (int i = 0; i < charsize; i++) rank[i + 1] += rank[i];
    for (int i = len - 1; i >= 0; i--) sa[--rank[wv[i]]] = y[i];
    std::swap(x, y);
    x[sa[0]] = 0;
    p = 1;
    for (int i = 1; i < len; i++) {
      p += !equals(y, sa[i], sa[i - 1], j);
      x[sa[i]] = p - 1;
    }
  }
}

template<typename T>
void calc_height(T *s, int *sa, int *h, int len) {
  for (int i = 1; i <= len; i++) rank[sa[i]] = i;
  for (int i = 0, k = 0; i < len; i++) {
    if (k > 0) k--;
    int j = sa[rank[i] - 1];
    while (s[i + k] == s[j + k]) k++;
    h[rank[i]] = k;
  }
}

template<typename T>
inline void print_sa(T *s, int start, int len, int offset) {
  for (int i = start; i <= len; i++) {
    int c = s[i] - offset + 'a';
    if (c >= 'a' && c <= 'z') {
      putchar(c);
    } else {
      printf("[%d]", s[i]);
    }
  }
  puts("");
}

void calc_rmq(int dp[MaxL][MaxN], int len) {
  to[0] = to[1] = 0;
  for (int i = 1; (i << 1) < MaxN; i++) {
    to[i << 1] = to[i << 1 | 1] = to[i] + 1;
  }

  for (int i = 1; (1 << i) <= len; i++) {
    for (int j = 0; j <= len; j++) {
      dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][std::min(len, j + (1 << (i - 1)))]);
    }
  }
}

inline int calc_min(int dp[MaxL][MaxN], int a, int b) {
  if (a > b) std::swap(a, b);
  a++;
  int r = to[b - a];
  return std::min(dp[r][a], dp[r][b + 1 - (1 << r)]);
}

/**
calc_sa(s, sa, len + 1, 128);
calc_height(s, sa, h, len);
*/

#endif /* SA_H */
