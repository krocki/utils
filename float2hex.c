#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint16_t u16;
typedef uint32_t u32;

typedef struct { u16 m:10, e:5, s:1; } hp;
typedef struct { u32 m:23, e:8, s:1; } sp;

typedef union { hp f; u16 h; } fp16;
typedef union { sp f; u32 h; float v; } fp32;

hp sp2hp(fp32 x) {
  x.h += 1<<(23-10-1);
  return (hp) {
    .m=x.f.e<113? 0: x.f.m >> (23-10),
    .e=x.f.e<113? 0: x.f.e - 127+15,
    .s=x.f.s
  };
}

sp hp2sp(hp h) {
  sp f = {0};
  f.e = (h.e - 15) + 127;
  if (0 == h.e) return f; // no denorms
  f.s = h.s;
  f.m = h.m << (23-10);
  return f;
}

int main(int argc, char **argv) {

  if (argc < 2) { printf("usage: %s val\n", argv[0]); return -1; }

  for (int i=1; i<argc; i++) {
    fp32 in = {.v=strtof(argv[i],NULL)};
    fp16 out = {.f=sp2hp(in)};
    fp32 trunc = {.f=hp2sp(out.f)};

    printf("in: %16.12g, "
           "fp32 (0x%08x), fp16 (0x%04x): %12.7g\n",
           in.v, in.h, out.h, trunc.v);
  }

  return 0;
}
