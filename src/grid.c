#include "grid.h"
#include "aabb.h"
#include "random.h"
#include "ship.h"
#include "vector.h"

Grid *generateGrid(Vector2 size) {
	Grid *grid = malloc(sizeof(Grid));
	if(grid != NULL) {
		grid->size = size;
	}
	return grid;
}

Ship generateShip(Grid *grid, int type) {
	Ship ship;
	ship.x = randRange(0, grid->size.x);
	ship.y = randRange(0, grid->size.y);
	ship.orientation = randRange(0, DIRECTIONS);
	ship.type = type;

	return ship;
}

Ship *generateShips(Grid *grid) {
	Ship *const ships = malloc(SHIP_TYPES * sizeof(Ship));
	const AABB bounds = getGridBounds(grid);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		bool validPosition = true;
		do {
			ships[i] = generateShip(grid, i);
			validPosition = shipIsValid(&ships[i], ships, i, bounds, 0);
		} while(!validPosition);
	}
	return ships;
}

AABB getGridBounds(Grid *grid) {
	return (AABB){0, 0, grid->size.x - 1, grid->size.y - 1};
}