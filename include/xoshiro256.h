#ifndef XOSHIRO256_H_
#define XOSHIRO256_H_

#include <stdint.h>

struct Xoshiro256 {
	uint64_t s[4];
};

struct Xoshiro256 initXoshiro256(uint64_t const seed);

uint64_t nextXoshiro256(struct Xoshiro256 *rng);

void seedXoshiro256(struct Xoshiro256 *rng, uint64_t const seed);

#endif /* XOSHIRO256_H_ */
