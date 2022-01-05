#include "grid.h"
#include "player.h"
#include "random.h"
#include "ship.h"
#include "vector.h"

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

	WINDOW *gridWindow = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 1);
	refresh();

	Grid *grid = generateGrid((Vector2){GRID_SIZE, GRID_SIZE}, gridWindow);
	Player player0 =
		createPlayer(getPlayerName(gridWindow), grid, generateShips(grid));
	Player player1 =
		createPlayer(getPlayerName(gridWindow), grid, generateShips(grid));

	Player *currentPlayer = &player0;

	int columns = getmaxx(stdscr);
	int rows = getmaxy(stdscr);
	int currentInput = 0;
	selectShip(&player0, 0);
	noecho();
	notimeout(gridWindow, true);
	cbreak();
	do {
		currentInput = getch();
		handleInput(&player0, currentInput);
		if(player0.requestsRedraw) {
			wclear(gridWindow);
			drawGrid(player0.grid);
			drawShips(player0.ships, player0.grid,
					  player0.isHoldingShip ? player0.currentShip : -1);
			if(!player0.isHoldingShip) {
				drawCursor(player0.grid, player0.cursor);
			}
			player0.requestsRedraw = false;
		}

	} while(true);
	endwin(); // end curses mode

	return 0;
}
