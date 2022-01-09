#include "events/drawArrangeShips.h"
#include "state.h"

StateType drawArrangeShips(StateType incomingType, Player *currentPlayer,
						   WINDOW *grid, WINDOW *name, WINDOW *info) {
	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;

	werase(grid);
	werase(name);
	mvwprintw(name, 0, size - (int)strlen(currentPlayer->name) / 2, "%s",
			  currentPlayer->name);
	drawGrid(grid, currentPlayer->grid);
	drawShips(grid, currentPlayer->ships, currentPlayer->grid,
			  currentPlayer->isHoldingShip ? currentPlayer->currentShip : -1);
	if(!currentPlayer->isHoldingShip) {
		drawCursor(grid, currentPlayer->grid, currentPlayer->cursor);
	}
	werase(info);
	char *shipName = getShipTypeName(currentPlayer->currentShip);
	mvwaddstr(info, 0, 0, "cursor: ");
	wattron(info, A_BOLD);
	wprintw(info, "%c%d", currentPlayer->cursor.x + 'A',
			currentPlayer->cursor.y + 1);
	wattroff(info, A_BOLD);
	waddstr(info, ", current ship: ");
	int color = getShipTypeColor(currentPlayer->currentShip);
	wattron(info, COLOR_PAIR(color));
	wprintw(info, "%s", shipName);
	wattroff(info, COLOR_PAIR(color));

	wrefresh(info);
	wrefresh(name);

	return ARRANGE_SHIPS;
}