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
