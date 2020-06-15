#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint16_t u16;
typedef uint32_t u32;

typedef struct { u16 m:10, e:5, s:1; } hp;
typedef struct { u32 m:23, e:8, s:1; } sp;

typedef union { hp f; u16 h; } fp16;
typedef union { sp f; u32 h; float v; } fp32;

sp hp2sp(hp h) {
  sp f = {0};
  f.e = (h.e - 15) + 127;
  if (0 == h.e) return f; // no denorms
  f.s = h.s;
  f.m = h.m << (23-10);
  return f;
}

void printbits(fp16 s) {

  // sign
  printf("%d ", (s.h >> 15) & 0x1);
  for (int i=14; i>=10; i--) printf("%d", (s.h >> i) & 0x1);
  printf(" ");
  for (int i=9; i>=0; i--) printf("%d", (s.h >> i) & 0x1);
  puts("");
}

int main(int argc, char **argv) {

  if (argc < 2) { printf("usage: %s hex\n", argv[0]); return -1; }

  for (int i=1; i<argc; i++) {
    fp16 in = {.h=(u16)strtol(argv[i], NULL, 16)};
    fp32 out = {.f=hp2sp(in.f)};
    printf("in: 0x%04x, out: %g (%.16f, 0x%08x)\n", in.h, out.v, out.v, out.h);
    //printbits(in);
  }

  return 0;

}
