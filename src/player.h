#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "grid.h"

typedef struct Player {
	char *name;
	bool requestsRedraw;
	bool isHoldingShip;
	Ship *currentShip;
	Vector2 cursor;
	Grid *grid;
	bool gridIsValid;
} Player;

Player createPlayer(char *name, Grid *grid);

char *getPlayerName(WINDOW *window);

void selectShip(Player *player, Ship *shipToSelect);
void deselectShip(Player *player);

void handleInput(Player *player, int input);

#endif // SRC_PLAYER_H_
