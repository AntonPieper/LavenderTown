#include "events/arrangeMode/drawArrangeShips.h"
#include "state.h"
#include "util/drawing.h"
#include <string.h>

StateType drawArrangeShips(
	StateType incomingType, Player *players, int currentPlayerIndex,
	WINDOW *enemyWindow, // NOLINT(bugprone-easily-swappable-parameters)
	WINDOW *gridWindow, WINDOW *nameWindow, WINDOW *infoWindow) {
	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;

	Player *currentPlayer = &players[currentPlayerIndex];

	werase(enemyWindow);
	werase(gridWindow);
	werase(nameWindow);
	werase(infoWindow);

	drawNameInCenter(nameWindow, currentPlayer->name);

	drawGrid(enemyWindow, players[1 - currentPlayerIndex].gridDimensions);
	drawGrid(gridWindow, currentPlayer->gridDimensions);
	drawShips(gridWindow, currentPlayer->ships, currentPlayer->gridDimensions,
			  currentPlayer->isHoldingShip ? (int)currentPlayer->currentShip
										   : -1);
	if(!currentPlayer->isHoldingShip) {
		drawCursor(gridWindow, currentPlayer->gridDimensions,
				   currentPlayer->cursor);
	}

	drawStats(infoWindow, currentPlayer->currentShip, currentPlayer->cursor);

	wrefresh(infoWindow);
	wrefresh(enemyWindow);
	wrefresh(gridWindow);
	wrefresh(nameWindow);

	return ARRANGE_SHIPS;
}