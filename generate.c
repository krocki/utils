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

void generate(u16 x, u16 y, u16 z, FILE *f) {

  for (u16 i=0; i<x; i++)
    for (u16 j=0; j<y; j++)
      for (u16 k=0; k<z; k++) {
        float v = (float)k+1.0f;
        fp32 f32 = { .v=v };
        fp16 f16 = { .f=sp2hp(f32) };
        if (NULL == f)
          printf("[%3u,%3u,%3u] = %6.2f, 0x%8x, 0x%04x\n", i, j, k, v, f32.h, f16.h);
        else {
          fwrite(&(f16.h), sizeof(u16), 1, f);
        }
      }
}

int main(int argc, char **argv) {

  if (argc < 4) {
    printf("usage: %s x y z\n", argv[0]);
    return -1;
  }

  long x = strtol(argv[1], NULL, 16);
  long y = strtol(argv[2], NULL, 16);
  long z = strtol(argv[3], NULL, 16);

  FILE *f = NULL;

  if (argc == 5) {
    char *fname = argv[4];
    f = fopen(fname, "wb");
  }

  generate(x, y, z, f);

  if (NULL != f) fclose(f);

  return 0;

}
