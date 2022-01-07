#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "cursor.h"
#include "grid.h"
#include "state.h"

typedef struct Player {
	char *name;

	bool isHoldingShip;
	int currentShip;

	Cursor cursor;

	Grid *grid;
	Ship ships[SHIP_TYPES];
} Player;

Player createPlayer(char *name, Grid *grid, Ship *ships);

void selectShip(Player *player, int index);
void deselectShip(Player *player);

#endif // SRC_PLAYER_H_
