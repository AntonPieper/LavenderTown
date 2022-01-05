#include "grid.h"
#include "player.h"
#include "random.h"
#include "ship.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define CASE(state, mask) if(((state) & (mask)) != 0U)

const int GRID_SIZE = 10;

int main() {
	srand(getSeed());
	initscr(); // start curses mode
	if(has_colors() == false) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();

	keypad(stdscr, true);

	init_pair(COLOR_CARRIER, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_BATTLESHIP, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_CRUISER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_SUBMARINE, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_DESTROYER, COLOR_BLACK, COLOR_CYAN);
	init_pair(COLOR_INVALID, COLOR_CYAN, COLOR_MAGENTA);

	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);

	WINDOW *gridWindow = newwin(rows - 1, columns, 1, 0);
	refresh();

	Grid *grid = generateGrid((Vector2){GRID_SIZE, GRID_SIZE}, gridWindow);
	Player player0 =
		createPlayer(getPlayerName(gridWindow), grid, generateShips(grid));
	wclear(gridWindow);
	Player player1 =
		createPlayer(getPlayerName(gridWindow), grid, generateShips(grid));

	Player *currentPlayer = &player0;

	selectShip(currentPlayer, 0);
	noecho();
	notimeout(gridWindow, true);
	cbreak();
	State state = IDLE;
	do {
		int currentInput = getch();
		state = handleInput(currentPlayer, currentInput);
		CASE(state, IDLE) {}
		CASE(state, NEXT_STEP) {
			currentPlayer = currentPlayer == &player0 ? &player1 : &player0;
		}
		CASE(state, REQUEST_REDRAW) {
			wclear(gridWindow);
			if(is_term_resized(rows, columns)) {
				getmaxyx(stdscr, rows, columns);
				wresize(gridWindow, rows - 1, columns);
			}
			move(0, 0);
			clrtoeol();
			mvprintw(0, (columns - (int)strlen(currentPlayer->name)) / 2, "%s",
					 currentPlayer->name);
			drawGrid(currentPlayer->grid);
			drawShips(currentPlayer->ships, currentPlayer->grid,
					  currentPlayer->isHoldingShip ? currentPlayer->currentShip
												   : -1);
			if(!currentPlayer->isHoldingShip) {
				drawCursor(currentPlayer->grid, currentPlayer->cursor);
			}
		}
	} while(state != QUIT);
	endwin(); // end curses mode

	return 0;
}
