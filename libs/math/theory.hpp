#ifndef THEORY_H
#define THEORY_H

bool not_prime[MaxN];
int primes[MaxN], phi[MaxN], f[MaxN], np;

void init_primes() {
  not_prime[1] = true;
  f[1] = 1;
  phi[1] = 1;
  for (int i = 2; i < MaxN; i++) {
    if (!not_prime[i]) {
      primes[np++] = i;
      phi[i] = i - 1;
      f[i] = -1;
    }
    for (int j = 0; j < np && i * primes[j] < MaxN; j++) {
      not_prime[i * primes[j]] = true;
      if (i % primes[j] == 0) {
        phi[i * primes[j]] = phi[i] * primes[j];
        f[i * primes[j]] = 0;
        break;
      }
      phi[i * primes[j]] = phi[i] * (primes[j] - 1);
      f[i * primes[j]] = -f[i];
    }
  }
}

void init_factors(std::vector<int> *factors) {
  for (int i = 1; i < MaxN; i++) {
    if (!f[i]) continue;
    for (int j = 1; i * j < MaxN; j++) {
      factors[i * j].push_back(i);
    }
  }
}

#endif /* THEORY_H */
