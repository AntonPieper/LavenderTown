#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include "ship.h"
#include "vector.h"
#include <curses.h>

typedef struct Grid {
	Vector2 size;
	WINDOW *window;
	Ship ships[SHIP_TYPES];
} Grid;

Grid *generateGrid(Vector2 size, WINDOW *window);

Ship *generateShips(Grid *grid);

void drawGrid(Grid *grid);

int getGridCellSizeX(Grid *grid);
int getGridCellSizeY(Grid *grid);

Vector2 getGridCellSize(Grid *grid);

void drawShips(Grid *grid);

#endif // SRC_GRID_H_
