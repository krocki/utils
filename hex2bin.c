/* loads hex file "abaacd..." and converts to bin */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "usage: %s hexfile binfile\n", argv[0]);
    return -1;
  }

  FILE *f0 = fopen(argv[1], "r");
  FILE *f1 = fopen(argv[2], "wb");

  assert(NULL != f0);
  assert(NULL != f1);

  char v[2];
  unsigned i=0;
  while (fread(v, sizeof(char), 2, f0)) {
    uint8_t b = strtoul(v, NULL, 16);
    fwrite(&b, sizeof b, 1, f1);
    i++;
  }

  printf("wrote %u bytes to %s\n", i, argv[2]);
  fclose(f0);
  fclose(f1);
  return 0;
}
