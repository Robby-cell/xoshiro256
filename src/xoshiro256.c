#include <stdio.h>
#include <stdint.h>

#include "xoshiro256.h"
#include "split.h"

static uint64_t _rotl(uint64_t const value, int shift) {
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;
	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}

static uint64_t _rotr(uint64_t const value, int shift) {
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;
	return (value >> shift) | (value << (sizeof(value) * 8 - shift));
}

struct Xoshiro256 initXoshiro256(uint64_t const seed) {
	struct Xoshiro256 rng;
	seedXoshiro256(&rng, seed);

	return rng;
}

uint64_t nextXoshiro256(struct Xoshiro256* rng) {
	uint64_t const r = _rotl(rng->s[0] + rng->s[3], 23) + rng->s[0];

	uint64_t const t = rng->s[1] << 17;

	rng->s[2] ^= rng->s[0];
	rng->s[3] ^= rng->s[1];
	rng->s[1] ^= rng->s[2];
	rng->s[0] ^= rng->s[3];

	rng->s[2] ^= t;

	rng->s[3] = _rotr(rng->s[3], 45);

	return r;
}

void seedXoshiro256(struct Xoshiro256* rng, uint64_t const seed) {
	seedSplit(seed);
	rng->s[0] = nextSplit();
	rng->s[1] = nextSplit();
	rng->s[2] = nextSplit();
	rng->s[3] = nextSplit();
}

