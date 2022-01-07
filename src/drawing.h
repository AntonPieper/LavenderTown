#ifndef SRC_DRAWING_H
#define SRC_DRAWING_H

#include "grid.h"
#include <curses.h>

void drawBox(WINDOW *window, AABB aabb);
void drawFilledBox(WINDOW *window, AABB aabb, int colorCode, bool drawOutline);

void drawGrid(WINDOW *window, Grid *grid);

void drawShip(WINDOW *window, Ship *shipRef, Grid *grid, Ship *ships,
			  bool drawOutline);
void drawShips(WINDOW *window, Ship *ships, Grid *grid, int highlightedShip);

void drawCursor(WINDOW *window, Grid *grid, Vector2 cursor);

int getGridCellSizeX(WINDOW *window, Grid *grid);
int getGridCellSizeY(WINDOW *window, Grid *grid);

Vector2 getGridCellSize(WINDOW *window, Grid *grid);

#endif // SRC_DRAWING_H