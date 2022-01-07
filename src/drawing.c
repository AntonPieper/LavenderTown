#include "drawing.h"
#include <curses.h>

void drawBox(WINDOW *window, AABB aabb) {
	WINDOW *borderBox =
		derwin(window, aabb.max.y - aabb.min.y + 1, aabb.max.x - aabb.min.x + 1,
			   aabb.min.y, aabb.min.x);
	wrefresh(window);
	box(borderBox, 0, 0);
	delwin(borderBox);
}

void drawFilledBox(WINDOW *window, AABB aabb, int colorCode, bool drawOutline) {
	WINDOW *filledBox =
		derwin(window, aabb.max.y - aabb.min.y + 1, aabb.max.x - aabb.min.x + 1,
			   aabb.min.y, aabb.min.x);
	wrefresh(window);
	wbkgd(filledBox, COLOR_PAIR(colorCode));
	if(drawOutline)
		wborder(filledBox, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD,
				ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD);
	mvwprintw(filledBox, aabb.min.y, aabb.min.x, "%d %d %d %d", aabb.min.x,
			  aabb.min.y, aabb.max.x, aabb.max.y);
	wrefresh(filledBox);
	delwin(filledBox);
}

void drawGrid(WINDOW *window, Grid *grid) {
	Vector2 cellSize = getGridCellSize(window, grid);
	const int maxX = (grid->size.x + 1) * cellSize.x;
	const int maxY = (grid->size.y + 1) * cellSize.y;

	drawBox(window, (AABB){0, 0, maxX, maxY});

	for(int x = 0; x < grid->size.x; ++x) {
		mvwaddch(window, 0, (x + 1) * cellSize.x, ACS_TTEE);
		mvwaddch(window, (grid->size.y + 1) * cellSize.y, (x + 1) * cellSize.x,
				 ACS_BTEE);

		mvwvline(window, 1, (x + 1) * cellSize.x, 0,
				 (grid->size.y + 1) * cellSize.y - 1);

		mvwprintw(window, cellSize.y / 2, (x + 1) * cellSize.x + cellSize.x / 2,
				  "%d", 1 + x);
	}
	for(int y = 0; y < grid->size.y; ++y) {
		mvwaddch(window, (y + 1) * cellSize.y, maxX, ACS_RTEE);
		mvwaddch(window, (y + 1) * cellSize.y, 0, ACS_LTEE);

		mvwhline(window, (y + 1) * cellSize.y, 1, 0, maxX - 1);

		mvwprintw(window, (y + 1) * cellSize.y + cellSize.y / 2,
				  (cellSize.x + 1) / 2, "%c", 'A' + y);
	}
	for(int y = 0; y < grid->size.y; ++y) {
		for(int x = 0; x < grid->size.x; ++x) {
			mvwaddch(window, (y + 1) * cellSize.y, (x + 1) * cellSize.x,
					 ACS_PLUS);
		}
	}

	wrefresh(window);
}

void drawShip(WINDOW *window, Ship *shipRef, Grid *grid, Ship *ships,
			  bool drawOutline) {
	Ship ship = *shipRef;
	ship.x += 1;
	ship.y += 1;
	Vector2 cellSize = getGridCellSize(window, grid);
	AABB shipCells = getOccupiedCells(ship);
	shipCells.max = add(shipCells.max, VECTOR2_ONE);

	shipCells.min = multiply(shipCells.min, cellSize);
	shipCells.max = multiply(shipCells.max, cellSize);

	shipCells.min.x += 1;
	shipCells.max.x -= 1;
	shipCells.max.y -= 1;
	if(cellSize.y > 1) {
		shipCells.min.y += 1;
	}

	int color = isValidShipMove(ships, getGridBounds(grid), shipRef, shipRef)
					? getShipTypeColor(ship.type)
					: COLOR_INVALID;

	drawFilledBox(window, shipCells, color, drawOutline);
}

void drawShips(WINDOW *window, Ship *ships, Grid *grid, int highlightedShip) {
	Vector2 cellSize = getGridCellSize(window, grid);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		Ship *ship = &ships[i];
		drawShip(window, ship, grid, ships, i == highlightedShip);
	}
	wrefresh(window);
}
void drawCursor(WINDOW *window, Grid *grid, Vector2 cursor) {
	Vector2 cellSize = getGridCellSize(window, grid);
	mvwaddch(window, (cursor.y + 1) * cellSize.y + cellSize.y / 2,
			 (cursor.x + 1) * cellSize.x + cellSize.x / 2, 'x');
	wrefresh(window);
}

int getGridCellSizeX(WINDOW *window, Grid *grid) {
	return (getmaxx(window) - 1) / (grid->size.x + 1);
}
int getGridCellSizeY(WINDOW *window, Grid *grid) {
	return (getmaxy(window) - 1) / (grid->size.y + 1);
}

Vector2 getGridCellSize(WINDOW *window, Grid *grid) {
	return (Vector2){getGridCellSizeX(window, grid),
					 getGridCellSizeY(window, grid)};
}