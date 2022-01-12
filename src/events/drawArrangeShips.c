#include "events/drawArrangeShips.h"
#include "state.h"
#include <string.h>

StateType drawArrangeShips(StateType incomingType, Player *currentPlayer,
						   WINDOW *gridWindow, WINDOW *nameWindow,
						   WINDOW *infoWindow) {
	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;

	werase(gridWindow);
	werase(nameWindow);
	mvwprintw(nameWindow, 0, size - (int)strlen(currentPlayer->name) / 2, "%s",
			  currentPlayer->name);
	drawGrid(gridWindow, currentPlayer->gridDimensions);
	drawShips(gridWindow, currentPlayer->ships, currentPlayer->gridDimensions,
			  currentPlayer->isHoldingShip ? currentPlayer->currentShip : -1);
	if(!currentPlayer->isHoldingShip) {
		drawCursor(gridWindow, currentPlayer->gridDimensions,
				   currentPlayer->cursor);
	}
	werase(infoWindow);
	char *shipName = getShipTypeName(currentPlayer->currentShip);
	mvwaddstr(infoWindow, 0, 0, "cursor: ");
	wattron(infoWindow, A_BOLD);
	wprintw(infoWindow, "%c%d", currentPlayer->cursor.x + 'A',
			currentPlayer->cursor.y + 1);
	wattroff(infoWindow, A_BOLD);
	waddstr(infoWindow, ", current ship: ");
	int color = getShipTypeColor(currentPlayer->currentShip);
	wattron(infoWindow, COLOR_PAIR(color));
	wprintw(infoWindow, "%s", shipName);
	wattroff(infoWindow, COLOR_PAIR(color));

	wrefresh(infoWindow);
	wrefresh(nameWindow);

	return ARRANGE_SHIPS;
}