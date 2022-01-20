#ifndef SRC_UTIL_RANDOM_H
#define SRC_UTIL_RANDOM_H

#include <stdlib.h>
#include <time.h>

///
/// \return a random integer x with the property min <= x < max
///
int randRange(int min, int max);

unsigned int getSeed();

#endif // SRC_UTIL_RANDOM_H