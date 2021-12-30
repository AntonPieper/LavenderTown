#include <curses.h>
#include <stdlib.h>

#include "grid.h"
#include "random.h"
#include "ship.h"
#include "vector.h"
#include <locale.h>

const int GRID_SIZE = 10;

int main() {
	srand(getSeed());
	initscr(); // start curses mode
	if(has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();

	init_pair(COLOR_CARRIER, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_BATTLESHIP, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_CRUISER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_SUBMARINE, COLOR_BLACK, COLOR_CYAN);
	init_pair(COLOR_DESTROYER, COLOR_BLACK, COLOR_MAGENTA);

	WINDOW *gridWindow = stdscr;
	refresh();
	Grid *grid =
		generateGrid((Vector2){GRID_SIZE, GRID_SIZE}, gridWindow);
	Ship *ships = generateShips(grid);
	// grid->ships[0] = (Ship){RIGHT,0,0,4};
	do {
		clear();
		drawGrid(grid);
		drawShips(grid);
		wrefresh(grid->window);
	} while(getch() == KEY_RESIZE);
	endwin(); // end curses mode

	return 0;
}
