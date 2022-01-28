#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "cursor.h"
#include "grid.h"
#include "state.h"
#include <stddef.h>

typedef struct Player {
	char *name;

	bool isHoldingShip;
	ShipType currentShip;

	Cursor cursor;

	Vector2 gridDimensions;

	Ship ships[SHIP_TYPES];

	HitInfo *hits;
} Player;

void selectShip(Player *player, int index);
void deselectShip(Player *player);

bool alreadyHit(int x, int y, HitInfo *hits, int gridWidth);
HitInfo getHitInfo(Player *enemy, Vector2 hitLocation, HitInfo *hits);

HitInfo attack(Player *player, Vector2 hitLocation, Player *enemy);

#endif // SRC_PLAYER_H
