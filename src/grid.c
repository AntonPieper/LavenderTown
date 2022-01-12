#include "grid.h"
#include "aabb.h"
#include "random.h"
#include "ship.h"
#include "vector.h"

Ship generateShip(Vector2 gridSize, int type) {
	Ship ship;
	ship.x = randRange(0, gridSize.x);
	ship.y = randRange(0, gridSize.y);
	ship.orientation = randRange(0, DIRECTIONS);
	ship.type = type;
	ship.sunk = false;

	return ship;
}

Ship *generateShips(Vector2 gridSize) {
	Ship *const ships = malloc(SHIP_TYPES * sizeof(Ship));
	const AABB bounds = getGridBounds(gridSize);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		bool validPosition = true;
		do {
			ships[i] = generateShip(gridSize, i);
			validPosition = shipIsValid(&ships[i], ships, i, bounds, 0);
		} while(!validPosition);
	}
	return ships;
}

AABB getGridBounds(Vector2 gridSize) {
	return (AABB){0, 0, gridSize.x - 1, gridSize.y - 1};
}