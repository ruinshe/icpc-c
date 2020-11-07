#include "libs/headers.h"

const int MaxN = 1005;
const long long INF = 0x3F3F3F3F3F3F3F3FLL;

int mp[MaxN][MaxN];
long long dp[MaxN][MaxN];
std::pair<int, long long> queue[MaxN][MaxN];
int f[MaxN], b[MaxN];
int N, M, K, U;

void init() {
  for (int i = 0; i < MaxN; i++) {
    dp[0][i] = dp[i][0] = -INF;
  }
}

inline void checkmax(long long &a, long long b) {
  if (a < b) {
    a = b;
  }
}

void solve() {
  scanf("%d%d%d%d", &N, &M, &K, &U);

  std::fill(f + 1, f + M + 1, 0);
  std::fill(b + 1, b + M + 1, 0);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      scanf("%d", &mp[i][j]);
      dp[i][j] = -INF;
    }
  }

  dp[1][1] = mp[1][1];
  for (int i = 1; i <= N; i++) {
    f[0] = b[0] = 0;
    for (int j = 1; j <= M; j++) {
      if (mp[i][j] <= 0) {
        continue;
      }
      while (f[j] < b[j] && queue[j][f[j]].first < i - K) {
        f[j]++;
      }
      while (f[0] < b[0] && queue[0][f[0]].first < j - K) {
        f[0]++;
      }

      for (int k = 1; k <= 3; k++) {
        const auto &ref = dp[i - (k & 1)][j - (k >> 1)];
        if (ref != -INF) {
          checkmax(dp[i][j], ref + mp[i][j]);
        }
      }

      if (f[0] < b[0]) {
        checkmax(dp[i][j], queue[0][f[0]].second + mp[i][j] - U);
      }
      if (f[j] < b[j]) {
        checkmax(dp[i][j], queue[j][f[j]].second + mp[i][j] - U);
      }

      if (dp[i][j] >= U) {
        while (f[j] < b[j] && queue[j][b[j] - 1].second <= dp[i][j]) {
          b[j]--;
        }
        queue[j][b[j]++] = {j, dp[i][j]};
      }
      while (f[0] < b[0] &&
             queue[0][b[0] - 1].second <= queue[j][f[j]].second) {
        b[0]--;
      }
      queue[0][b[0]++] = {std::min(j - (i - queue[j][f[j]].first), j),
                          queue[j][f[j]].second};

      fprintf(stderr, "%d %d %d (%d)\n", i, j, dp[i][j], dp[i][j] == -INF);
    }
  }

  printf("%lld\n", dp[N][M] == -INF ? -1 : dp[N][M]);
}
