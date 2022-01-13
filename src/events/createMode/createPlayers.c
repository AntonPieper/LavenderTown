#include "events/createMode/createPlayers.h"
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
static const size_t BACKSPACE_LENGTH = sizeof(BACKSPACE) / sizeof(*BACKSPACE);

static const KeyMapping NEXT_PLAYER[] = {'\n', 1, KEY_ENTER, 1};
static const size_t NEXT_PLAYER_LENGTH =
	sizeof(NEXT_PLAYER) / sizeof(*NEXT_PLAYER);

void *allocateNewStringSize(size_t oldSize, char *string, size_t newSize) {
	if(oldSize <= 0) {
		return malloc(newSize);
	}
	return realloc(string, newSize);
}

StateType createPlayers(StateType incomingType, Player players[2],
						int *currentPlayerIndex) {
	Player *currentPlayer = &players[*currentPlayerIndex];
	char *const oldName = currentPlayer->name;
	const size_t oldLength = oldName == NULL ? 0 : strlen(oldName);

	int input = getInput(-1);
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
	if(getMappedValue(NEXT_PLAYER_LENGTH, NEXT_PLAYER, input)) {
		if(!oldName)
			currentPlayer->name = calloc(1, sizeof(char));
		Ship *ships = generateShips(currentPlayer->gridDimensions);
		memcpy(currentPlayer->ships, ships, SHIP_TYPES * sizeof(*ships));
		free(ships);
		currentPlayer->currentShip = -1;
		if(!currentPlayer->hits) {
			currentPlayer->hits =
				calloc((size_t)currentPlayer->gridDimensions.x *
						   currentPlayer->gridDimensions.y,
					   sizeof(*currentPlayer->hits));
			if(!currentPlayer->hits)
				return QUIT;
		}
		if(++*currentPlayerIndex > 1) {
			*currentPlayerIndex = 0;
			return DRAW_ARRANGE_SHIPS;
		}
		return DRAW_CREATE_PLAYERS;
	}
	return CREATE_PLAYERS;
}