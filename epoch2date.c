#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {

  if (argc<2) {
    printf("usage: %s epochtime\n", argv[0]);
    return -1;
  }

  uint64_t us = strtoul(argv[1], NULL, 10);
  uint32_t seconds = us / 1000000;
  uint32_t minutes = seconds / 60;
  uint32_t hours = minutes / 60;
  uint32_t days = hours / 24;

  printf("us=%llu, s=%u, m=%u, h=%u, d=%u\n",
    us, seconds, minutes, hours, days);
}
