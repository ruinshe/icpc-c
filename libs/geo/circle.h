#ifndef CIRCLE_H
#define CIRCLE_H

const double PI = acos(-1.0);
const double eps = 1e-16;

struct circle_t {
  double x, y, r;
};

double area(const circle_t &circle) {
  return PI * circle.r * circle.r;
}

double common_area(const circle_t &A, const circle_t &B) {
  double s = 0.0;
  const circle_t &M = (A.r > B.r) ? A : B;
  const circle_t &N = (A.r > B.r) ? B : A;
  double D = hypot(N.x - M.x, N.y - M.y);
  if ((D < M.r + N.r - eps) && (D > M.r - N.r + eps)) {
    double cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
    double cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
    double alpha = 2.0 * acos(cosM);
    double beta = 2.0 * acos(cosN);
    double TM = 0.5 * M.r * M.r * sin(alpha);
    double TN = 0.5 * N.r * N.r * sin(beta);
    double FM = (alpha / (2.0 * PI)) * area(M);
    double FN = (beta / (2.0 * PI)) * area(N);
    s = FM + FN - TM - TN;
  } else if (D < M.r - N.r + eps) {
    s = area(N);
  }
  return s;
}

#endif
