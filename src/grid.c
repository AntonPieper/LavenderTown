#include "grid.h"
#include "aabb.h"
#include "random.h"
#include "ship.h"
#include "vector.h"
#include <stdbool.h>

Grid *generateGrid(Vector2 size, WINDOW *window) {
	Grid *grid = malloc(sizeof(Grid) + SHIP_TYPES * sizeof(Ship));
	if(grid != NULL) {
		grid->size = size;
		grid->window = window;
	}
	return grid;
}
void drawBox(WINDOW *window, int minX, int minY, int maxX, int maxY) {
	WINDOW *borderBox =
		derwin(window, maxY - minY + 1, maxX - minX + 1, minX, minX);
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

void drawGrid(Grid *grid) {
	Vector2 cellSize = getGridCellSize(grid);
	const int maxX = (grid->size.x + 1) * cellSize.x;
	const int maxY = (grid->size.y + 1) * cellSize.y;

	drawBox(grid->window, 0, 0, maxX, maxY);

	for(int x = 0; x < grid->size.x; ++x) {
		mvwaddch(grid->window, 0, (x + 1) * cellSize.x, ACS_TTEE);
		mvwaddch(grid->window, (grid->size.y + 1) * cellSize.y,
				 (x + 1) * cellSize.x, ACS_BTEE);

		mvwvline(grid->window, 1, (x + 1) * cellSize.x, 0,
				 (grid->size.y + 1) * cellSize.y - 1);

		mvwprintw(grid->window, cellSize.y / 2,
				  (x + 1) * cellSize.x + cellSize.x / 2, "%d", 1 + x);
	}
	for(int y = 0; y < grid->size.y; ++y) {
		mvwaddch(grid->window, (y + 1) * cellSize.y, maxX, ACS_RTEE);
		mvwaddch(grid->window, (y + 1) * cellSize.y, 0, ACS_LTEE);

		mvwhline(grid->window, (y + 1) * cellSize.y, 1, 0, maxX - 1);

		mvwprintw(grid->window, (y + 1) * cellSize.y + cellSize.y / 2,
				  (cellSize.x + 1) / 2, "%c", 'A' + y);
	}
	for(int y = 0; y < grid->size.y; ++y) {
		for(int x = 0; x < grid->size.x; ++x) {
			mvwaddch(grid->window, (y + 1) * cellSize.y, (x + 1) * cellSize.x,
					 ACS_PLUS);
		}
	}

	wrefresh(grid->window);
}

bool shipIsValid(Ship *ship, Grid *grid, const int numShips,
				 Ship *ignoredShip) {
	AABB shipCells = getOccupiedCells(*ship);
	if(!isInsideBounds(ship, grid))
		return false;
	Ship *const ships = grid->ships;
	for(int i = 0; i < numShips; ++i) {
		if(&ships[i] == ignoredShip)
			continue;
		if(intersects(shipCells, getOccupiedCells(ships[i])))
			return false;
	}
	return true;
}
bool isValidMove(Grid *grid, Ship *currentShip, Ship *newShip) {
	return shipIsValid(newShip, grid, SHIP_TYPES, currentShip);
}
bool isInsideBounds(Ship *ship, Grid *grid) {
	AABB shipCells = getOccupiedCells(*ship);
	return inside((AABB){0, 0, grid->size.x - 1, grid->size.y - 1}, shipCells);
}
Ship generateShip(Grid *grid, int type) {
	Ship ship;
	ship.x = randRange(0, grid->size.x);
	ship.y = randRange(0, grid->size.y);
	ship.orientation = randRange(0, ORIENTATIONS);
	ship.type = type;

	return ship;
}

Ship *generateShips(Grid *grid) {
	Ship *const ships = grid->ships;
	for(int i = 0; i < SHIP_TYPES; ++i) {
		bool validPosition = true;
		do {
			ships[i] = generateShip(grid, i);
			validPosition = shipIsValid(&ships[i], grid, i, 0);
		} while(!validPosition);
	}
	return ships;
}

void drawShip(Grid *grid, int id, bool drawOutline) {
	Ship shipRef = grid->ships[id];
	Ship ship = shipRef;
	ship.x += 1;
	ship.y += 1;
	Vector2 cellSize = getGridCellSize(grid);
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

	int color = isValidMove(grid, &grid->ships[id], &grid->ships[id])
					? getShipTypeColor(ship.type)
					: COLOR_INVALID;

	drawFilledBox(grid->window, shipCells, color, drawOutline);
}

void drawShips(Grid *grid, Ship *highlightedShip) {
	Vector2 cellSize = getGridCellSize(grid);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		drawShip(grid, i, highlightedShip == &grid->ships[i]);
	}
	wrefresh(grid->window);
}
void drawCursor(Grid *grid, Vector2 cursor) {
	Vector2 cellSize = getGridCellSize(grid);
	mvwaddch(grid->window, (cursor.y + 1) * cellSize.y + cellSize.y / 2,
			 (cursor.x + 1) * cellSize.x + cellSize.x / 2, 'x');
	wrefresh(grid->window);
}
int getGridCellSizeX(Grid *grid) {
	return (getmaxx(grid->window) - 1) / (grid->size.x + 1);
}
int getGridCellSizeY(Grid *grid) {
	return (getmaxy(grid->window) - 1) / (grid->size.y + 1);
}

Vector2 getGridCellSize(Grid *grid) {
	return (Vector2){getGridCellSizeX(grid), getGridCellSizeY(grid)};
}
