#include "events/arrangeShips.h"
#include "events/attackMode.h"
#include "events/createPlayers.h"
#include "events/drawArrangeShips.h"
#include "events/drawAttackMode.h"
#include "events/drawCreatePlayers.h"
#include "player.h"
#include "random.h"
#include "ship.h"
#include "state.h"
#include <curses.h>
#include <string.h>

const int GRID_SIZE = 10;
typedef struct World {
	WINDOW *gridWindow;
	WINDOW *nameWindow;
	WINDOW *infoWindow;
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
									 world->currentPlayerIndex,
									 world->gridWindow);
		case ARRANGE_SHIPS:
			return arrangeShips(incomingType, world->players,
								&world->currentPlayerIndex, world->input);
		case DRAW_ARRANGE_SHIPS:
			return drawArrangeShips(
				incomingType, &world->players[world->currentPlayerIndex],
				world->gridWindow, world->nameWindow, world->infoWindow);

		case ATTACK_MODE:
			return attackMode(incomingType, world->players,
							  &world->currentPlayerIndex, world->input);
		case DRAW_ATTACK_MODE:
			return drawAttackMode(incomingType, world->players,
								  world->currentPlayerIndex, world->gridWindow);
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
	init_pair(COLOR_NO_HIT, COLOR_WHITE, COLOR_CYAN);
	init_pair(COLOR_HIT, COLOR_BLACK, COLOR_RED);
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

	world.gridWindow = gridWindow;
	world.infoWindow = infoWindow;
	world.nameWindow = nameWindow;

	Vector2 gridDimensions = {GRID_SIZE, GRID_SIZE};
	world.players[0].gridDimensions = gridDimensions;
	world.players[1].gridDimensions = gridDimensions;

	noecho();
	nodelay(gridWindow, true);
	keypad(gridWindow, true);
	cbreak();
	StateType state = DRAW_CREATE_PLAYERS;
	do {
		world.input = wgetch(gridWindow);
		state = handleState(state, &world);
	} while(state != QUIT);
	endwin(); // end curses mode

	return 0;
}
