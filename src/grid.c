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
	wmove(window, minY, minX);
	waddch(window, ACS_ULCORNER);
	whline(window, 0, maxX - minX - 1);
	mvwaddch(window, minY, maxX, ACS_URCORNER);
	wmove(window, maxY, minX);
	waddch(window, ACS_LLCORNER);
	whline(window, 0, maxX - minX - 1);
	mvwaddch(window, maxY, maxX, ACS_LRCORNER);
	mvwvline(window, minY + 1, minX, 0, maxY - minY - 1);
	mvwvline(window, minY + 1, maxX, 0, maxY - minY - 1);
}
void drawFilledBox(WINDOW *window, AABB box, int colorCode) {
	attron(COLOR_PAIR(colorCode));
	for(int y = box.min.y; y <= box.max.y; ++y)
		mvwhline(window, y, box.min.x, ' ', box.max.x - box.min.x + 1);
	attroff(COLOR_PAIR(colorCode));
}
void drawGrid(Grid *grid) {
	// box(grid->window, 0, 0);
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

bool shipIsValid(int shipId, Grid *grid) {
	Ship ship = grid->ships[shipId];
	AABB shipCells = getOccupiedCells(ship);
	if(shipCells.min.x < 0 || shipCells.min.y < 0 ||
	   shipCells.max.x >= grid->size.x || shipCells.max.y >= grid->size.y)
		return false;
	Ship *const ships = grid->ships;
	const int numShips = shipId; // Only consider initialized ships
	for(int i = 0; i < shipId; ++i) {
		if(intersects(shipCells, getOccupiedCells(ships[i])))
			return false;
	}
	return true;
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
			validPosition = shipIsValid(i, grid);
			wrefresh(grid->window);
			mvwprintw(grid->window, 0, 0, "Ship: {%d, %d, %d, %5s}    %7s\n",
					  ships[i].x, ships[i].y, getShipTypeLength(ships[i].type),
					  getOrientationName(ships[i].orientation),
					  validPosition ? "VALID" : "INVALID");
		} while(!validPosition);
	}
	return ships;
}

void drawShip(Grid *grid, int id) {
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
	drawFilledBox(grid->window, shipCells, getShipTypeColor(ship.type));
}

void drawShips(Grid *grid) {
	Vector2 cellSize = getGridCellSize(grid);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		drawShip(grid, i);
	}
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
