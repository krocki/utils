#include <stdio.h>

/* determine endianness */
int main(int argc, char **argv) {

  int n = 1;
  int e = (1 == *(char*) &n);
  puts(e ? "le" : "be");

  return e;
}
