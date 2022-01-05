#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "grid.h"

typedef struct Player {
	char *name;

	bool isHoldingShip;
	int currentShip;

	Vector2 cursor;

	Grid *grid;
	Ship ships[SHIP_TYPES];
} Player;

typedef enum State {
	IDLE = 0U,
	REQUEST_REDRAW = 1U,
	NEXT_STEP = 2U,
	QUIT = 4U
} State;

Player createPlayer(char *name, Grid *grid, Ship *ships);

char *getPlayerName(WINDOW *window);

void selectShip(Player *player, int index);
void deselectShip(Player *player);

State handleInput(Player *player, int input);

#endif // SRC_PLAYER_H_
