#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <queue>
#include <vector>
#include <numeric>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <tuple>
#include <cassert>

#include "io.h"

namespace {

#define for_each_test_cases(T, BUFFSIZE)            \
  TokenizeReader reader(::stdin, BUFFSIZE);         \
  int T;                                            \
  scanf("%d", &T);                                  \
  for (int cas = 1; cas <= T; cas++)

}  // namesapce
