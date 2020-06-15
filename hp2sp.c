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

int main(int argc, char **argv) {

  if (argc < 2) { printf("usage: %s hex\n", argv[0]); return -1; }

  for (int i=1; i<argc; i++) {
    fp16 in = {.h=(u16)strtol(argv[i], NULL, 16)};
    fp32 out = {.f=hp2sp(in.f)};
    printf("in: 0x%04x, out: %7.3g \tfp32 (%12.7g, 0x%08x)\n", in.h, out.v, out.v, out.h);
    //printbits(in);
  }

  return 0;

}
