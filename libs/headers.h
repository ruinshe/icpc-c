#include <bits/stdc++.h>

void init();
void solve();

int main() {
  init();
#ifdef IDEA_TIME_EVALUATE
  double time_sum = 0, cases = 0;
  clock_t max_time_cost = 0;
#endif
#ifndef SINGLE_CASE
  while (scanf("%*[ \t\n]*") != EOF) {
#endif
#ifdef IDEA_TIME_EVALUATE
    clock_t start = clock();
#endif
    solve();
#ifdef IDEA_TIME_EVALUATE
    clock_t end = clock();
    max_time_cost = std::max(max_time_cost, end - start);
    time_sum += end - start;
    cases++;
#endif
#ifndef SINGLE_CASE
  }
#endif
#ifdef IDEA_TIME_EVALUATE
  fprintf(stderr,
          "[INFO] Solution ends with %.0f ms (average %.0f ms), and maximum "
          "time case in single case is %.0f ms.\n",
          time_sum * 1000.0 / CLOCKS_PER_SEC,
          time_sum * 1000.0 / CLOCKS_PER_SEC / cases,
          max_time_cost * 1000.0 / CLOCKS_PER_SEC);
#endif
  return 0;
}
