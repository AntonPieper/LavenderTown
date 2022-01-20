#include <stdlib.h>
#include <time.h>

int randRange(int min, int max) { return (rand() % (max - min)) + min; }

unsigned int getSeed() {
	time_t t = 0;
	return time(&t);
}