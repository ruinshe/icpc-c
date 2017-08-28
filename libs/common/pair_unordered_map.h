#ifndef PAIR_UNORDERED_MAP_H
#define PAIR_UNORDERED_MAP_H

#include <utility>

struct int_pair_hash_t {
  int operator()(const std::pair<int, int>& p) const {
    // ignored overflow.
    return 31 * p.first + p.second;
  }
};

#endif // PAIR_UNORDERED_MAP_H
