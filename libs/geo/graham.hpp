#ifndef GRAHAM_H
#define GRAHAM_H


template<typename T>
double graham(point_t<T>* p, int n) {
  static point_t<T> stack[MaxS];
  double res = 0.0;
  int top = 0;

  if (n < 3) return 0.0;

  std::sort(p, p + n, compCoord<double>);
  stack[top++] = p[1];
  stack[top++] = p[2];

  for (int i = 3; i <= n; i++) {
    while (top >= 2 && xmult(p[i], stack[top - 1], stack[top - 2]) >= 0) top--;
    stack[top++] = p[i];
  }

  int tmp = top;
  for (int i = n - 1; i >= 1; i--) {
    while (top != tmp && xmult(p[i], stack[top - 1], stack[top - 2]) >= 0) top--;
    stack[top++] = p[i];
  }
  top--;

  for (int i = 0; i < top; i++) res += stack[i] * stack[i + 1];
  printf("res = %.12f\n", fabs(res) / 2.0);
  return fabs(res) / 2.0;
}

#endif