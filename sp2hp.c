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

int main(int argc, char **argv) {

  if (argc < 2) { printf("usage: %s val\n", argv[0]); return -1; }

  for (int i=1; i<argc; i++) {
    fp32 in = {.h=(u32)strtol(argv[i],NULL, 16)};
    fp16 out = {.f=sp2hp(in)};

    printf("in: 0x%08x, %12.7g, "
           "fp16 (0x%04x)\n",
           in.h, in.v, out.h);
  }

  return 0;
}
