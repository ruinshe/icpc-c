#include <bits/stdc++.h>

void init();
void solve();

int main() {
  init();
#ifndef SINGLE_CASE
  while (scanf("%*[ \t\n]*") != EOF) {
#endif
#ifdef IDEA_TIME_EVALUATE
    clock_t start = clock();
#endif
    solve();
#ifdef IDEA_TIME_EVALUATE
    clock_t end = clock();
    fprintf(stderr, "INFO: Solution ends with %.0f ms.\n",
            (end - start) * 1000.0 / CLOCKS_PER_SEC);
#endif
#ifndef SINGLE_CASE
  }
#endif
  return 0;
}
