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

bool shipIsValid(Ship *ship, Grid *grid, int numShips, Ship *ignoredShip);
bool isValidMove(Grid *grid, Ship *currentShip, Ship *newShip);
bool isInsideBounds(Ship *ship, Grid *grid);

Ship *generateShips(Grid *grid);

void drawGrid(Grid *grid);

int getGridCellSizeX(Grid *grid);
int getGridCellSizeY(Grid *grid);

Vector2 getGridCellSize(Grid *grid);

void drawShip(Grid *grid, int id, bool drawOutline);
void drawShips(Grid *grid, Ship *highlightedShip);

void drawCursor(Grid *grid, Vector2 cursor);

#endif // SRC_GRID_H_
