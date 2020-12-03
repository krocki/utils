/* array save - example */

#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "usage: %s binfile\n", argv[0]);
    return -1;
  }

  float arr[] = {.1f, 1e-3f, .123443f};

  FILE *f = fopen(argv[1], "wb");
  assert(NULL != f);

  fwrite(arr, sizeof arr, 1, f);

  fclose(f);

  return 0;
}
