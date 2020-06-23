#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {

  if (argc < 6) {
    printf("usage: %s offset stride count file [new_val]\n", argv[0]);
    return -1;
  }

  unsigned long offset = strtoul(argv[1], NULL, 16);
  unsigned long stride = strtoul(argv[2], NULL, 16);
  unsigned long count =  strtoul(argv[3], NULL, 16);
  char *in_name = argv[4];
  unsigned long new_val =  strtoul(argv[5], NULL, 16);

  printf("offset=%u, stride=%u, count=%u, in=%s, newval=%u\n",
    offset, stride, count, in_name, new_val);

  FILE *f = fopen(in_name, "rb+");

  if (!f) { printf("error opening %s\n", in_name); return -1; }

  unsigned pos = offset;

  fseek(f, 0, SEEK_END);
  unsigned len = ftell(f);
  rewind(f);

  printf("%s: length = %u B\n", in_name, len);

  unsigned n=0;

  while (n<count || (count==0 && pos<len)) {

    uint16_t v;
    fseek(f, pos, SEEK_SET);
    fread(&v, sizeof(uint16_t), 1, f);
    printf("%u, pos = %u, value read = 0x%04x\n", n, pos, v);
    fseek(f, pos, SEEK_SET);
    fwrite(&new_val, sizeof(uint16_t), 1, f);
    pos += sizeof(uint16_t) * stride;
    n++;
  }

  fclose(f);
  return 0;

}
