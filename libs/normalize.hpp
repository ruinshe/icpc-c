int normalize(int* a, int n, bool modify_elements = false) {
  static int idx[MaxN];
  for (int i = 0; i < n; i++) idx[i] = i;
  std::sort(idx, idx + n, [&](const int& i, const int& j) { return a[i] < a[j]; });
  int last = a[idx[0]], m = 0;
  if (modify_elements) a[idx[0]] = m++;
  for (int i = 1; i < n; i++) {
    if (a[idx[i]] == last) {
      a[idx[i]] = m - 1;
    } else {
      last = a[idx[i]];
      if (modify_elements) a[idx[i]] = m++;
    }
  }
  return m;
}
