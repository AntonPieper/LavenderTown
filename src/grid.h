#ifndef SRC_GRID_H
#define SRC_GRID_H

#include "ship.h"
#include "util/vector.h"

int getIndex(int x, int y, int width);

Ship *generateShips(Vector2 gridSize);

AABB getGridBounds(Vector2 gridSize);

#endif // SRC_GRID_H
