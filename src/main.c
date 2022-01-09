#include "events/arrangeShips.h"
#include "events/createPlayers.h"
#include "events/drawCreatePlayers.h"
#include "player.h"
#include "random.h"
#include "ship.h"
#include "state.h"
#include <curses.h>
#include <string.h>

const int GRID_SIZE = 10;
typedef struct World {
	WINDOW *window;
	int input;
	Player players[2];
	int currentPlayerIndex;
} World;

StateType handleState(StateType incomingType, World *world) {
	switch(incomingType) {
		case CREATE_PLAYERS:
			return createPlayers(incomingType, world->players,
								 &world->currentPlayerIndex, world->input);
		case DRAW_CREATE_PLAYERS:
			return drawCreatePlayers(incomingType, world->players,
									 world->currentPlayerIndex, world->window);
		case ARRANGE_SHIPS:
			return arrangeShips(incomingType, world->players,
								&world->currentPlayerIndex, world->input);
		case ATTACK_MODE: return QUIT;
		default: return incomingType;
	}
}

int main() {
	srand(getSeed());
	initscr(); // start curses mode
	if(has_colors() == false) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();

	init_pair(COLOR_CARRIER, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_BATTLESHIP, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_CRUISER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_SUBMARINE, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_DESTROYER, COLOR_BLACK, COLOR_CYAN);
	init_pair(COLOR_INVALID, COLOR_CYAN, COLOR_MAGENTA);

	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;
	if(size * 2 > columns)
		columns = size * 2;

	WINDOW *gridWindow = newwin(size, size * 2, 1, 0);
	WINDOW *nameWindow = newwin(1, size * 2, 0, 0);
	WINDOW *infoWindow = newwin(1, size * 2, rows - 1, 0);
	refresh();

	World world = {0};

	world.window = gridWindow;

	world.players[0].grid = generateGrid((Vector2){GRID_SIZE, GRID_SIZE});
	world.players[1].grid = generateGrid((Vector2){GRID_SIZE, GRID_SIZE});

	noecho();
	nodelay(gridWindow, true);
	keypad(gridWindow, true);
	cbreak();
	StateType state = DRAW_CREATE_PLAYERS;
	do {
		world.input = wgetch(gridWindow);
		state = handleState(state, &world);
		if(state == DRAW_ARRANGE_SHIPS) {
			werase(gridWindow);
			werase(nameWindow);
			Player *currentPlayer = &world.players[world.currentPlayerIndex];
			mvwprintw(nameWindow, 0,
					  size - (int)strlen(currentPlayer->name) / 2, "%s",
					  currentPlayer->name);
			drawGrid(world.window, currentPlayer->grid);
			drawShips(world.window, currentPlayer->ships, currentPlayer->grid,
					  currentPlayer->isHoldingShip ? currentPlayer->currentShip
												   : -1);
			if(!currentPlayer->isHoldingShip) {
				drawCursor(world.window, currentPlayer->grid,
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

			state = ARRANGE_SHIPS;
			wrefresh(infoWindow);
			wrefresh(nameWindow);
		}
	} while(state != QUIT);
	endwin(); // end curses mode

	return 0;
}
