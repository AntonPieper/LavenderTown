#include "player.h"
#include "ship.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const int MAX_PLAYER_NAME_LENGTH = 64;

const char ENTER_YOUR_NAME_MESSAGE[] = "Enter your name: ";

void selectShip(Player *player, int index) {
	if(index > -1 && index < SHIP_TYPES) {
		player->currentShip = index;
		player->isHoldingShip = true;
	}
}

void deselectShip(Player *player) { player->isHoldingShip = false; }

bool alreadyHit(int x, int y, HitInfo *hits, int gridWidth) {
	return hits[getIndex(x, y, gridWidth)].type != INVALID_HIT;
}
void setHitInfoType(HitInfo *hits, int gridWidth, AABB cells, HitType type) {
	for(int y = cells.min.y; y < cells.max.y; ++y)
		for(int x = cells.min.x; x < cells.max.x; ++x) {
			int index = getIndex(x, y, gridWidth);
			hits[index].type = type;
		}
}
HitInfo getHitInfo(Player *enemy, Vector2 hitLocation, HitInfo *hits) {
	HitInfo hitInfo;
	hitInfo.type = NO_HIT;
	hitInfo.hitShip = NULL;

	int shipIndex = getShipTypeAtPosition(hitLocation, enemy->ships);
	if(shipIndex == -1) {
		return hitInfo;
	}

	Ship *hitShip = &enemy->ships[shipIndex];
	AABB cells = getOccupiedCells(*hitShip);

	int hitLocationIndex =
		getIndex(hitLocation.x, hitLocation.y, enemy->gridDimensions.x);

	bool destroyed = true;
	for(int y = cells.min.y; y <= cells.max.y; ++y)
		for(int x = cells.min.x; x <= cells.max.x; ++x) {
			int index = getIndex(x, y, enemy->gridDimensions.x);
			if(index == hitLocationIndex)
				continue;
			destroyed =
				destroyed && alreadyHit(x, y, hits, enemy->gridDimensions.x);
		}
	hitInfo.type = destroyed ? DESTROYED : HIT;
	hitInfo.hitShip = hitShip;
	return hitInfo;
}

HitInfo attack(Player *player, Vector2 hitLocation, Player *enemy) {
	HitInfo hitInfo = getHitInfo(enemy, hitLocation, player->hits);
	if(hitInfo.type == DESTROYED) {
		hitInfo.hitShip->sunk = true;
		const int shipLength = getShipTypeLength(hitInfo.hitShip->type);
		const Vector2 offset = {};
		setHitInfoType(player->hits, player->gridDimensions.x,
					   getOccupiedCells(*hitInfo.hitShip), DESTROYED);
	}
	player->hits[getIndex(hitLocation.x, hitLocation.y,
						  player->gridDimensions.x)] = hitInfo;
	return hitInfo;
}