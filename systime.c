#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

uint64_t usec() {

  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000 + tv.tv_usec);

}

int main(int argc, char **argv) {

  //while (1) {
  //  printf( "\tnow: %6.6f\r", sec());
  //  fflush(stdout);
  //  usleep(100000);
  //}

  fprintf(stdout, "%llu\n", usec());
  return 0;

}
