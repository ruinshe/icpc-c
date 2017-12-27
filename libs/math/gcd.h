#ifndef GCD_H
#define GCD_H

template<typename T>
T gcd(T a, T b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}

// a * x + b * y = 1
// for a * x + b * y = n, check n % g == 0 then x, y *= n / g
// minimum x: (x % (b / g) + (b / g)) % (b / g)
// need to double check whether y >= 0 or not if needed.
long long e_gcd(long long a, long long b, long long& x, long long& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long g = e_gcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

#endif // GCD_H
