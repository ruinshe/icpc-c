#ifndef UTILS_H
#define UTILS_H

#include <cstdio>

namespace {

auto default_print_function = [](const int& x) -> void {
  printf("%d ", x);
};

#define print_dp_arrays2(mp, INF, n, m)                     \
  {                                                         \
    for (int i_ = 0; i_ < (n); i_++) {                      \
      for (int j_ = 0; j_ < (m); j_++) {                    \
        if (dp[i_][j_] != INF) {                            \
          printf("dp[%d][%d] = %d\n", i_, j_, dp[i_][j_]);  \
        }                                                   \
      }                                                     \
    }                                                       \
  }

#define print_matrix4(mp, n, m, print_function) \
  {                                             \
    for (int i_ = 0; i_ < (n); i_++) {          \
      for (int j_ = 0; j_ < (m); j_++) {        \
        print_function(mp[i_][j_]);             \
      }                                         \
      puts("");                                 \
    }                                           \
  }
#define print_matrix(mp, n, m) print_matrix(mp, n, m, default_print_function)

}  // namespace

#endif  // UTILS_H

