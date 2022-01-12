#include "events/createPlayers.h"
#include "grid.h"
#include "input.h"
#include "player.h"
#include "state.h"
#include <ctype.h>
#include <curses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const KeyMapping BACKSPACE[] = {127, 1, KEY_BACKSPACE, 1, '\b', 1};
static const size_t BACKSPACE_LENGTH = sizeof(BACKSPACE) / sizeof(BACKSPACE[0]);

static const KeyMapping SWITCH_PLAYER[] = {'\n', 1, KEY_ENTER, 1};
static const size_t SWITCH_PLAYER_LENGTH =
	sizeof(SWITCH_PLAYER) / sizeof(SWITCH_PLAYER[0]);

void *allocateNewStringSize(size_t oldSize, char *string, size_t newSize) {
	if(oldSize <= 0) {
		return malloc(newSize);
	}
	return realloc(string, newSize);
}

StateType createPlayers(StateType incomingType, Player players[2],
						int *currentPlayerIndex, int input) {
	Player *currentPlayer = &players[*currentPlayerIndex];
	char *const oldName = currentPlayer->name;
	const size_t oldLength = oldName == NULL ? 0 : strlen(oldName);

	if(isgraph(input) || input == ' ') {
		currentPlayer->name =
			allocateNewStringSize(oldLength, oldName, oldLength + 1);
		char *const name = currentPlayer->name;
		if(name == NULL)
			return QUIT;
		name[oldLength] = (char)input;
		return DRAW_CREATE_PLAYERS;
	}
	if((oldName && oldName[0] != '\0') &&
	   getMappedValue(BACKSPACE_LENGTH, BACKSPACE, input)) {
		currentPlayer->name[oldLength - 1] = '\0';
		if(oldLength > 1) {
			currentPlayer->name =
				allocateNewStringSize(oldLength, oldName, oldLength - 1);
		}
		return DRAW_CREATE_PLAYERS;
	}
	if(getMappedValue(SWITCH_PLAYER_LENGTH, SWITCH_PLAYER, input)) {
		if(!oldName)
			currentPlayer->name = malloc(sizeof(char));
		Ship *ships = generateShips(currentPlayer->gridDimensions);
		memcpy(currentPlayer->ships, ships, SHIP_TYPES * sizeof(*ships));
		++*currentPlayerIndex;
		if(*currentPlayerIndex > 1) {
			*currentPlayerIndex = 0;
			return DRAW_ARRANGE_SHIPS;
		}
		return DRAW_CREATE_PLAYERS;
	}

	if(!currentPlayer->hits) {
		players[*currentPlayerIndex].hits =
			calloc((size_t)currentPlayer->gridDimensions.x *
					   currentPlayer->gridDimensions.y,
				   sizeof(*currentPlayer->hits));
		if(!currentPlayer->hits)
			return QUIT;
	}
	return CREATE_PLAYERS;
}