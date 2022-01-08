#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include "ship.h"
#include "vector.h"

typedef struct Grid {
	Vector2 size;
} Grid;

Grid *generateGrid(Vector2 size);

Ship *generateShips(Grid *grid);

AABB getGridBounds(Grid *grid);

#endif // SRC_GRID_H_
