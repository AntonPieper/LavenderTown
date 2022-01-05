#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include "ship.h"
#include "vector.h"
#include <curses.h>

typedef struct Grid {
	Vector2 size;
	WINDOW *window;
} Grid;

Grid *generateGrid(Vector2 size, WINDOW *window);

Ship *generateShips(Grid *grid);

void drawGrid(Grid *grid);

int getGridCellSizeX(Grid *grid);
int getGridCellSizeY(Grid *grid);

Vector2 getGridCellSize(Grid *grid);

AABB getGridBounds(Grid *grid);

void drawShip(Ship *shipRef, Grid *grid, Ship *ships, bool drawOutline);
void drawShips(Ship *ships, Grid *grid, int highlightedShip);

void drawCursor(Grid *grid, Vector2 cursor);

#endif // SRC_GRID_H_
