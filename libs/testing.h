#ifndef TESTING_H
#define TESTING_H

#define TEST(actual, expected) \
  if ((actual) == (expected)) printf("\033[0;32mP\033[0m"); \
  else printf("\033[0;31mF\033[0m");

#endif // TESTING_H
