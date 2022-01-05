#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_

#include "aabb.h"
#include "vector.h"

#define COLOR_CARRIER 1
#define COLOR_BATTLESHIP 2
#define COLOR_CRUISER 3
#define COLOR_SUBMARINE 4
#define COLOR_DESTROYER 5
#define COLOR_INVALID 6

typedef enum Orientation { UP, RIGHT, DOWN, LEFT } Orientation;
#define ORIENTATIONS 4
char *getOrientationName(Orientation orientation);

typedef enum ShipType {
	CARRIER,
	BATTLESHIP,
	CRUISER,
	SUBMARINE,
	DESTROYER
} ShipType;
#define SHIP_TYPES 5
char *getShipTypeName(ShipType shipType);

int getShipTypeLength(ShipType shipType);
int getShipTypeColor(ShipType shipType);

typedef struct Ship {
	Orientation orientation;
	int x, y;
	ShipType type;
} Ship;

AABB getOccupiedCells(Ship ship);

///
/// \returns found ship, else NULL
///
Ship *getShipAtPosition(Vector2 position, Ship *ships, int numShips);
///
/// \returns found ship, else -1
///
int getShipIndexAtPosition(Vector2 position, Ship *ships, int numShips);

bool shipIsValid(Ship *ship, Ship *ships, int numShips, AABB bounds,
				 Ship *ignoredShip);
bool isValidMove(Ship *ships, AABB bounds, Ship *currentShip, Ship *newShip);
bool isInsideBounds(Ship *ship, AABB bounds);

#endif // SRC_SHIP_H_
