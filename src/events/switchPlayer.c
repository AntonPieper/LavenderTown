#include "events/switchPlayer.h"
#include "input.h"
#include "state.h"
#include "util/drawing.h"
#include <stddef.h>
#include <string.h>

static const char SWITCH_PLAYER_STRING[] = "'s turn!";
static const int SWITCH_PLAYER_STRING_LENGTH =
	sizeof(SWITCH_PLAYER_STRING) / sizeof(*SWITCH_PLAYER_STRING) - 1;

static const char PROMPT_STRING[] = "Press any key to continue";
static const int PROMPT_STRING_LENGTH =
	sizeof(PROMPT_STRING) / sizeof(*PROMPT_STRING) - 1;
StateType switchPlayer(StateType incomingType, Player *players,
					   int *currentPlayerIndex, WINDOW *window) {
	werase(window);
	const int columns = getmaxx(window);
	const int rows = getmaxy(window);
	*currentPlayerIndex = 1 - *currentPlayerIndex;
	const Player *const player = &players[*currentPlayerIndex];
	const char *const name = player->name;
	const int nameLength = (int)strlen(name);

	const int messageLength = nameLength + SWITCH_PLAYER_STRING_LENGTH + 1;
	char message[messageLength];
	memset(message, 0, messageLength);
	strcat(message, name);
	strcat(message, SWITCH_PLAYER_STRING);
	const int boxSize = PROMPT_STRING_LENGTH > messageLength
							? PROMPT_STRING_LENGTH
							: messageLength;
	AABB box;
	box.min.x = (columns - boxSize) / 2 - 4;
	box.max.x = (columns + boxSize) / 2 + 4;
	box.min.y = rows / 2 - 4;
	box.max.y = rows / 2 + 4;
	mvwprintw(window, rows / 2 - 2, (columns - messageLength) / 2, "%s",
			  message);
	mvwprintw(window, rows / 2 + 2, (columns - PROMPT_STRING_LENGTH) / 2, "%s",
			  PROMPT_STRING);
	drawBox(window, box);

	getInput(-1);
	return incomingType;
}

StateType switchPlayerFullScreen(StateType incomingType, Player *players,
								 int *currentPlayerIndex) {
	return switchPlayer(incomingType, players, currentPlayerIndex, stdscr);
}