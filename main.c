#include <stdio.h>

#include "xoshiro256.h"
#include "split.h"

int main(void) {
  struct Xoshiro256 rng = { 0 };
  seedSplit(trueRandomSeed());
  seedXoshiro256(&rng, nextSplit());

  for (int i = 0; i < 20; ++i) {
    // die
    uint64_t num = nextXoshiro256(&rng) % 6 + 1;
    printf("%ld\n", num);
  }
}
