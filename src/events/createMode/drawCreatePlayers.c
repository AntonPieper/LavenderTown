#include "events/createMode/drawCreatePlayers.h"
#include "events/createMode/createPlayers.h"
#include "state.h"
#include "util/drawing.h"
#include "windows.h"
#include <string.h>

const char MESSAGE[] = "Enter your name:";
const int MESSAGE_LENGTH = 16;
const char PLAYER_INDEX_MESSAGE[] = "Player";
const int PLAYER_INDEX_MESSAGE_LENGTH = 6;

StateType drawCreatePlayers(StateType incomingType, Player *players,
							int playerIndex, PlayerWindows windows) {
	werase(windows.main);

	int columns = getmaxx(windows.main);
	int rows = getmaxy(windows.main);
	char *name = players[playerIndex].name;
	int nameLength = name == NULL ? 0 : (int)strlen(name);
	AABB box;
	box.min.x = (columns - nameLength - MESSAGE_LENGTH) / 2 - 4;
	box.max.x = (columns + nameLength + MESSAGE_LENGTH) / 2 + 4;
	box.min.y = rows / 2 - 2;
	box.max.y = rows / 2 + 2;
	drawBox(windows.main, box);
	mvwprintw(windows.main, box.min.y,
			  (columns - PLAYER_INDEX_MESSAGE_LENGTH - 2) / 2, "%s %1d",
			  PLAYER_INDEX_MESSAGE, playerIndex + 1);
	mvwprintw(windows.main, rows / 2,
			  (columns - nameLength - MESSAGE_LENGTH - 1) / 2, "%s", MESSAGE);
	if(name != NULL)
		mvwprintw(windows.main, rows / 2,
				  (columns - nameLength - MESSAGE_LENGTH - 1) / 2 +
					  MESSAGE_LENGTH + 1,
				  "%s", name);

	wrefresh(windows.main);
	return CREATE_PLAYERS;
}
