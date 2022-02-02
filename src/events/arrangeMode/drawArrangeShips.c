#include "events/arrangeMode/drawArrangeShips.h"
#include "playerWindows.h"
#include "state.h"
#include "util/drawing.h"
#include <string.h>

StateType drawArrangeShips(StateType incomingType, Player *players,
						   int currentPlayerIndex, PlayerWindows windows) {
	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;

	Player *currentPlayer = &players[currentPlayerIndex];

	eraseAllWindows(&windows);

	drawNameInCenter(windows.name, currentPlayer->name);

	drawGrid(windows.tracking, players[1 - currentPlayerIndex].gridDimensions);
	drawGrid(windows.primary, currentPlayer->gridDimensions);
	drawShips(windows.primary, currentPlayer->ships,
			  currentPlayer->gridDimensions,
			  currentPlayer->isHoldingShip ? currentPlayer->currentShip : -1);
	if(!currentPlayer->isHoldingShip) {
		drawCursor(windows.primary, currentPlayer->gridDimensions,
				   currentPlayer->cursor);
	}

	drawStats(windows.info, currentPlayer->currentShip, currentPlayer->cursor);

	overwriteMainWindow(&windows);
	wrefresh(windows.main);
	return ARRANGE_SHIPS;
}