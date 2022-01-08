#include "input.h"

const KeyMapping *findMapping(size_t numMappings, const KeyMapping *mappings,
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