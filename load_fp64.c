/* load an fp64 array from file */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "usage: %s binfile\n", argv[0]);
    return -1;
  }

  FILE *f = fopen(argv[1], "rb");
  assert(NULL != f);

  int i = 0;

  union {
    double f;
    uint64_t h;
  } v;

  while (fread(&v, sizeof(double), 1, f)) {
    printf("[%05d] 0x%08x: %9.6f\n", i++, v.h, v.f);
  }

  fclose(f);
  return 0;
}
