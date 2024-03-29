#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "split.h"

static uint64_t x;

uint64_t nextSplit(void) {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

double nextFloatSplit(void) {
	return nextSplit() / pow(2.0, 64);
}

void seedSplit(uint64_t const initial) {
	x = initial;
}

uint64_t trueRandomSeed(void) {
#define COUNT 8
  uint64_t buf;
  printf("buf: %ld\n", buf);

  // 318	getrandom	man/ cs/	0x13e	char *buf	size_t count	unsigned int flags	-	-	-

  asm volatile(
    "syscall"
    :
    : "rax" (0x13e),
      "rdi" (&buf),
      "rsi" (COUNT),
      "rdx" (0)
    :
  );
  printf("buf: %ld\n", buf);

  return buf;
  #undef COUNT
}
