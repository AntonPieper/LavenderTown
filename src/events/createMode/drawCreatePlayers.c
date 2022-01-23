#include "events/createMode/drawCreatePlayers.h"
#include "events/createMode/createPlayers.h"
#include "state.h"
#include "util/drawing.h"
#include <string.h>

const char MESSAGE[] = "Enter your name:";
const int MESSAGE_LENGTH = 16;
const char PLAYER_INDEX_MESSAGE[] = "Player";
const int PLAYER_INDEX_MESSAGE_LENGTH = 6;

StateType drawCreatePlayers(StateType incomingType, Player *players,
							int playerIndex, WINDOW *window) {
	wclear(window);
	int columns = getmaxx(window);
	int rows = getmaxy(window);
	char *name = players[playerIndex].name;
	int nameLength = name == NULL ? 0 : (int)strlen(name);
	AABB box;
	box.min.x = (columns - nameLength - MESSAGE_LENGTH) / 2 - 4;
	box.max.x = (columns + nameLength + MESSAGE_LENGTH) / 2 + 4;
	box.min.y = rows / 2 - 2;
	box.max.y = rows / 2 + 2;
	drawBox(window, box);
	mvwprintw(window, box.min.y,
			  (columns - PLAYER_INDEX_MESSAGE_LENGTH - 2) / 2, "%s %1d",
			  PLAYER_INDEX_MESSAGE, playerIndex + 1);
	mvwprintw(window, rows / 2, (columns - nameLength - MESSAGE_LENGTH - 1) / 2,
			  "%s", MESSAGE);
	if(name != NULL)
		mvwprintw(window, rows / 2,
				  (columns - nameLength - MESSAGE_LENGTH - 1) / 2 +
					  MESSAGE_LENGTH + 1,
				  "%s", name);
	wrefresh(window);
	return CREATE_PLAYERS;
}
