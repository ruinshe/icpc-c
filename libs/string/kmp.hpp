#ifndef KMP_H
#define KMP_H

const int next[MaxN];

void build_pattern(const char* s, int len) {
  next[0] = -1;
  for (int i = 1, j = -1; i < len; i++) {
    while (j >= 0 && s[j + 1] != s[i]) j = next[j];
    if (s[j + 1] == s[i]) j++;
    next[i] = j;
  }
}

int kmp(const char* s, int len, const char* pattern, const int* next, int pattern_len) {
  for (int i = 0, j = -1; i < len; i++) {
    while (j >= 0 && pattern[j + 1] != s[i]) j = next[j];
    if (pattern[j + 1] == a[i]) j++;
    // KMP[i] = j + 1;
}
}

#endif // KMP_H
