#include <bits/stdc++.h>

void solve();

int main() {
#ifdef IDEA_TIME_EVALUATE
  freopen("data.in", "r", stdin);
#endif
  while (scanf("%*[ \t\n]*") != EOF) {
#ifdef IDEA_TIME_EVALUATE
    clock_t start = clock();
#endif
    solve();
#ifdef IDEA_TIME_EVALUATE
    clock_t end = clock();
    fprintf(stderr, "INFO: Solution ends with %.0f ms.\n",
            (end - start) * 1000.0 / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}

