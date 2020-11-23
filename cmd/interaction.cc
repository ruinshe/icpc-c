#include "testlib.h"

// ouf is the user output, and write user stdin into stdout.
int main(int argc, char **argv) {
  setName("basic interaction logic implementation");
  registerInteraction(argc, argv);

  fclose(stdout);
  ouf.readEof();
  quitf(_ok, "0 cases");
}
