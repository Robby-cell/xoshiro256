#ifndef SPLIT_H_
#define SPLIT_H_

#include <stdint.h>

uint64_t trueRandomSeed(void);

uint64_t nextSplit(void);

double nextFloatSplit(void);

void seedSplit(uint64_t const initial);

#endif /* SPLIT_H_ */
