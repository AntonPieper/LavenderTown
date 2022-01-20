#include "events/arrangeMode/arrangeShips.h"
#include "events/arrangeMode/drawArrangeShips.h"
#include "events/attackMode/attackPlayer.h"
#include "events/attackMode/drawAttackPlayer.h"
#include "events/attackMode/drawSwitchAttackingPlayer.h"
#include "events/attackMode/switchAttackingPlayer.h"
#include "events/createMode/createPlayers.h"
#include "events/createMode/drawCreatePlayers.h"
#include "locale.h"
#include "player.h"
#include "ship.h"
#include "state.h"
#include "util/random.h"
#include <curses.h>
#include <string.h>

const int GRID_SIZE = 10;

typedef struct World {
	WINDOW *enemyWindow;
	WINDOW *gridWindow;
	WINDOW *nameWindow;
	WINDOW *infoWindow;
	Player players[2];
	int currentPlayerIndex;
} World;

StateType handleState(StateType incomingType, World *world) {
	switch(incomingType) {
		case CREATE_PLAYERS:
			return createPlayers(incomingType, world->players,
								 &world->currentPlayerIndex);
		case DRAW_CREATE_PLAYERS:
			return drawCreatePlayers(incomingType, world->players,
									 world->currentPlayerIndex, stdscr);
		case ARRANGE_SHIPS:
			return arrangeShips(incomingType, world->players,
								&world->currentPlayerIndex);
		case DRAW_ARRANGE_SHIPS:
			return drawArrangeShips(incomingType, world->players,
									world->currentPlayerIndex,
									world->enemyWindow, world->gridWindow,
									world->nameWindow, world->infoWindow);
		case ATTACK_MODE:
			return attackPlayer(incomingType, world->players,
								world->currentPlayerIndex);
		case DRAW_ATTACK_MODE:
			return drawAttackPlayer(incomingType, world->players,
									world->currentPlayerIndex,
									world->enemyWindow, world->gridWindow,
									world->nameWindow, world->infoWindow);
		case SWITCH_ATTACKING_PLAYER:
			return switchAttackingPlayer(incomingType, world->players,
										 &world->currentPlayerIndex);
		case DRAW_SWITCH_ATTACKING_PLAYER:
			return drawSwitchAttackingPlayer(
				incomingType, world->players, world->currentPlayerIndex,
				world->enemyWindow, world->gridWindow, world->nameWindow,
				world->infoWindow);
		default: return incomingType;
	}
}

int main() {
	setlocale(LC_ALL, "");
	srand(getSeed());
	initscr(); // start curses mode
	if(has_colors() == false) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();

	init_pair(COLOR_CARRIER, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_BATTLESHIP, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_CRUISER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_SUBMARINE, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_DESTROYER, COLOR_BLACK, COLOR_CYAN);
	init_pair(COLOR_INVALID, COLOR_CYAN, COLOR_MAGENTA);

	init_pair(COLOR_NO_HIT, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_HIT, COLOR_RED, COLOR_BLACK);

	int rows = getmaxy(stdscr);
	int columns = getmaxx(stdscr);
	int size = rows - 2;
	// if(columns < size * 2)
	//	size = columns / 2;
	int enemyGridSize = GRID_SIZE + 2;
	int playerGridSize = size - enemyGridSize;

	WINDOW *enemyWindow = newwin(enemyGridSize, enemyGridSize * 2, 1, 0);
	WINDOW *gridWindow = newwin(playerGridSize, playerGridSize * 2,
								1 + enemyGridSize, enemyGridSize * 2);
	WINDOW *nameWindow = newwin(1, size * 2, 0, 0);
	WINDOW *infoWindow = newwin(1, size * 2, rows - 1, 0);
	refresh();

	World world = {0};

	world.enemyWindow = enemyWindow;
	world.gridWindow = gridWindow;
	world.infoWindow = infoWindow;
	world.nameWindow = nameWindow;

	Vector2 gridDimensions = {GRID_SIZE, GRID_SIZE};
	world.players[0].gridDimensions = gridDimensions;
	world.players[1].gridDimensions = gridDimensions;

	noecho();
	keypad(stdscr, true);
	cbreak();
	StateType state = DRAW_CREATE_PLAYERS;
	do {
		state = handleState(state, &world);
	} while(state != QUIT);
	endwin(); // end curses mode

	return 0;
}
