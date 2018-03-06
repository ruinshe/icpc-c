#ifndef HASHING_H
#define HASHING_H

#include <string>
#include <unordered_set>

#ifndef MaxN
#define MaxN 100005
#endif

namespace hashing {

  const long long HASH_F[] = {257, 318, 1007};
  const long long HASH_MOD[] = {100003, 10000019, 100000037};
  const long long HASH_MOD_REV[] = {76656, 9842786, 29592861};

  long long hash_pow[3][MaxN];
  long long hash_pow_rev[3][MaxN];
  static bool hash_inited = false;

  void hash_init() {
    for (int i = 0; i < 3; i++) {
      hash_pow[i][0] = hash_pow_rev[i][0] = 1;
      for (int j = 1; j < MaxN; j++) {
        hash_pow[i][j] = (hash_pow[i][j - 1] * HASH_F[i]) % HASH_MOD[i];
        hash_pow_rev[i][j] =
          (hash_pow_rev[i][j - 1] * HASH_MOD_REV[i]) % HASH_MOD[i];
      }
    }
    hash_inited = true;
  }

  struct hash_value {
    long long values[3];

    hash_value() {
      values[0] = values[1] = values[2] = 0;
    }

    size_t operator()(const hash_value& value) const {
      return (size_t) (value.values[0] * HASH_F[1]
                       + value.values[1] + HASH_MOD[2] + value.values[2]);
    }

    hash_value operator-(const hash_value& other) const {
      hash_value result;
      for (int i = 0; i < 3; i++) {
        result.values[i] = values[i] - other.values[i];
        if (result.values[i] < 0) {
          result.values[i] += HASH_MOD[i];
        }
      }
      return result;
    }

    bool operator==(const hash_value& other) const {
      return values[0] == other.values[0]
        && values[1] == other.values[1]
        && values[2] == other.values[2];
    }

    bool operator!=(const hash_value& other) const {
      return values[0] != other.values[0]
        || values[1] != other.values[1]
        || values[2] != other.values[2];
    }
  };

  typedef std::unordered_set<hash_value, hash_value> hash_value_table;

  struct hash_t {
    hash_value hash_values[MaxN];
    int length;

    // calculates the hash value of sub-sequence [from, to).
    hash_value slice(int from, int to) const {
      hash_value value;
      if (from >= to) return value;
      if (from == 0) {
        return hash_values[to - 1];
      } else {
        from--;
        to--;
        // change to (from, to]
        for (int i = 0; i < 3; i++) {
          value.values[i] =
            hash_values[to].values[i] - hash_values[from].values[i];
          value.values[i] %= HASH_MOD[i];
          if (value.values[i] < 0) value.values[i] += HASH_MOD[i];
          value.values[i] =
            (value.values[i] * hash_pow_rev[i][from + 1]) % HASH_MOD[i];
        }
      }
      return value;
    }
  };

  void hash(const char* s, const int& n, hash_t& result) {
    if (!hash_inited) hash_init();
    result.length = n;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < n; j++) {
        if (j == 0) {
          result.hash_values[j].values[i] = s[j];
        } else {
          result.hash_values[j].values[i] =
            (result.hash_values[j - 1].values[i] + s[j] * hash_pow[i][j])
            % HASH_MOD[i];
        }
      }
    }
  }

  void hash(const std::string& s, hash_t& result) {
    hash(s.c_str(), s.length(), result);
  }
}

#endif // HASHING_H
