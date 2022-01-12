#ifndef SRC_DRAWING_H
#define SRC_DRAWING_H

#include "cursor.h"
#include "grid.h"
#include <curses.h>

void drawBox(WINDOW *window, AABB aabb);
void drawFilledBox(WINDOW *window, AABB aabb, int colorCode, bool drawOutline);

void drawGrid(WINDOW *window, Vector2 gridDimensions);

void drawShip(WINDOW *window, Ship *shipRef, Vector2 gridDimensions,
			  Ship *ships, bool drawOutline);
void drawShips(WINDOW *window, Ship *ships, Vector2 gridDimensions,
			   int highlightedShip);

void drawCursor(WINDOW *window, Vector2 gridDimensions, Cursor cursor);

void drawHits(WINDOW *window, Vector2 gridDimensions,
			  HitInfo hits[gridDimensions.x * gridDimensions.y]);

int getGridCellSizeX(WINDOW *window, Vector2 gridDimensions);
int getGridCellSizeY(WINDOW *window, Vector2 gridDimensions);

Vector2 getGridCellSize(WINDOW *window, Vector2 gridDimensions);

#endif // SRC_DRAWING_H