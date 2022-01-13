#include "input.h"
#include <curses.h>
#include <time.h>

const KeyMapping *findMapping(size_t numMappings,
							  const KeyMapping mappings[numMappings],
							  int input) {
	for(size_t i = 0; i < numMappings; ++i)
		if(mappings[i].key == input)
			return &mappings[i];
	return NULL;
}

int getMappedValue(size_t numMappings, const KeyMapping *mappings, int input) {
	for(size_t i = 0; i < numMappings; ++i)
		if(mappings[i].key == input)
			return mappings[i].value;
	return 0;
}

int getInput(int delay) {
	if(!delay)
		return getch();
	timeout(delay);
	const int ch = getch();
	timeout(-1);
	return ch;
}

void delay(double seconds) {
	/* save start time */
	const time_t start = time(NULL);

	time_t current = 0;
	do {
		/* get current time */
		time(&current);

		/* break loop when the requested number of seconds have elapsed */
	} while(difftime(current, start) < seconds);
}