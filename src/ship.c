#include "ship.h"
#include "util/aabb.h"

const int CARRIER_LENGTH = 5;
const int BATTLESHIP_LENGTH = 4;
const int CRUISER_LENGTH = 3;
const int SUBMARINE_LENGTH = 3;
const int DESTROYER_LENGTH = 2;

char *getOrientationName(Orientation orientation) {
	switch(orientation) {
		case DIR_UP: return "UP";
		case DIR_RIGHT: return "RIGHT";
		case DIR_DOWN: return "DOWN";
		case DIR_LEFT: return "LEFT";
		default: return "INVALID";
	}
}

char *getShipTypeName(ShipType shipType) {
	switch(shipType) {
		case CARRIER: return "Carrier";
		case BATTLESHIP: return "Battleship";
		case CRUISER: return "Cruiser";
		case SUBMARINE: return "Submarine";
		case DESTROYER: return "Destroyer";
		default: return "Invalid";
	}
}

int getShipTypeLength(ShipType shipType) {
	switch(shipType) {
		case CARRIER: return CARRIER_LENGTH;
		case BATTLESHIP: return BATTLESHIP_LENGTH;
		case CRUISER: return CRUISER_LENGTH;
		case SUBMARINE: return SUBMARINE_LENGTH;
		case DESTROYER: return DESTROYER_LENGTH;
		default: return 0;
	}
}

int getShipTypeColor(ShipType shipType) {
	switch(shipType) {
		case CARRIER: return COLOR_CARRIER;
		case BATTLESHIP: return COLOR_BATTLESHIP;
		case CRUISER: return COLOR_CRUISER;
		case SUBMARINE: return COLOR_SUBMARINE;
		case DESTROYER: return COLOR_DESTROYER;
		default: return 0;
	}
}

AABB getOccupiedCells(Ship ship) {
	int len = getShipTypeLength(ship.type) - 1;
	switch(ship.orientation) {
		case DIR_UP: return (AABB){ship.x, ship.y - len, ship.x, ship.y};
		case DIR_RIGHT: return (AABB){ship.x, ship.y, ship.x + len, ship.y};
		case DIR_DOWN: return (AABB){ship.x, ship.y, ship.x, ship.y + len};
		case DIR_LEFT: return (AABB){ship.x - len, ship.y, ship.x, ship.y};
		default: return (AABB){ship.x, ship.y, ship.x + len, ship.y};
	}
}
Ship *getShipAtPosition(Vector2 position, Ship ships[]) {
	int shipId = getShipTypeAtPosition(position, ships);
	if(shipId == -1)
		return 0;
	return &ships[shipId];
}
ShipType getShipTypeAtPosition(Vector2 position, Ship ships[]) {
	for(int i = 0; i < SHIP_TYPES; ++i) {
		if(pointInside(getOccupiedCells(ships[i]), position))
			return i;
	}
	return INVALID;
}

bool shipIsValid(Ship *ship, Ship ships[], int numShips, AABB bounds,
				 Ship *ignoredShip) {
	AABB shipCells = getOccupiedCells(*ship);
	if(!shipInsideBounds(ship, bounds))
		return false;
	if(!ships)
		return true;
	for(int i = 0; i < numShips; ++i) {
		if(&ships[i] == ignoredShip)
			continue;
		if(intersects(shipCells, getOccupiedCells(ships[i])))
			return false;
	}
	return true;
}
bool isValidShipMove(Ship ships[], AABB bounds, Ship *currentShip,
					 Ship *newShip) {
	return shipIsValid(newShip, ships, SHIP_TYPES, bounds, currentShip);
}
bool shipInsideBounds(Ship *ship, AABB bounds) {
	AABB shipCells = getOccupiedCells(*ship);
	return inside(bounds, shipCells);
}
