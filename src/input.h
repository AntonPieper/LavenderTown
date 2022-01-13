#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include <stddef.h>

typedef struct KeyMapping {
	int key;
	int value;
} KeyMapping;

///
/// \returns first mapping for given input. If non is found, returns NULL
/// \todo implement some kind of hashmap for faster access
///
const KeyMapping *findMapping(size_t numMappings,
							  const KeyMapping mappings[numMappings],
							  int input);

int getMappedValue(size_t numMappings, const KeyMapping *mappings, int input);

///
/// If delay < 0: infinite timeout
/// Else if delay == 0: no timeout
/// Else: delay milliseconds timeout
///
int getInput(int delay);

void delay(double seconds);

#endif // SRC_INPUT_H