#ifndef INT128_H
#define INT128_H

struct int100_t {
  long long high, low;

  int100_t() : high(0), low(0) {}
  int100_t(long long _low) : high(_low >> 50), low(_low & ((1LL << 50) - 1)) {}
  int100_t(long long _high, long long _low) : high(_high), low(_low) {}
  int100_t operator|(const int100_t& other) const {
    return int100_t(high | other.high, low | other.low);
  }
  int100_t& operator|=(const int100_t& other) {
    high |= other.high;
    low |= other.low;
    return *this;
  }
  int100_t operator&(const int100_t& other) const {
    return int100_t(high & other.high, low & other.low);
  }
  int100_t operator^(const int100_t& other) const {
    return int100_t(high ^ other.high, low ^ other.low);
  }
  int100_t operator<<(const int& d) const {
    return int100_t((high << d) | (low >> (50 - d)), low << d);
  }
  int bitcount() const { return __builtin_popcountll(high) + __builtin_popcountll(low); }
  bool operator==(const int100_t& other) const {
    return high == other.high && low == other.low;
  }
};

#endif
