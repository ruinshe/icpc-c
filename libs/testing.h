#ifndef TESTING_H
#define TESTING_H

#define TEST_BEGIN clock_t test_begin = clock(); Solution solution

#define TEST_END clock_t test_end = clock();                            \
  printf("\n\nTotal_time_cost: %.3f s\n",                              \
         (double) (test_end - test_begin) / CLOCKS_PER_SEC)

#define TEST(delegator, expected) {                                     \
    clock_t begin = clock();                                            \
    auto actual = delegator;                                            \
    clock_t end = clock();                                              \
    if ((int) (end - begin) > 2 * CLOCKS_PER_SEC)                       \
      printf("\033[0;34mT\033[0m");                                     \
    else if ((actual) == (expected)) printf("\033[0;32mP\033[0m");      \
    else printf("\033[0;31mF\033[0m");                                  \
    fflush(stdout);                                                     \
  }

#endif // TESTING_H
