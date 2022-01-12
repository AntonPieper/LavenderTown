#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include "ship.h"
#include "vector.h"

Ship *generateShips(Vector2 gridSize);

AABB getGridBounds(Vector2 gridSize);

#endif // SRC_GRID_H_
