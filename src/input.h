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
const KeyMapping *findMapping(size_t numMappings, const KeyMapping *mappings,
							  int input);

int getMappedValue(size_t numMappings, const KeyMapping *mappings, int input);

#endif // SRC_INPUT_H