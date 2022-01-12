#include "drawing.h"
#include "cursor.h"
#include "ship.h"
#include <curses.h>

void drawBox(WINDOW *window, AABB aabb) {
	WINDOW *borderBox =
		derwin(window, aabb.max.y - aabb.min.y + 1, aabb.max.x - aabb.min.x + 1,
			   aabb.min.y, aabb.min.x);
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
	delwin(filledBox);
}

void drawGrid(WINDOW *window, Vector2 gridDimensions) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	const int maxX = (gridDimensions.x + 1) * cellSize.x;
	const int maxY = (gridDimensions.y + 1) * cellSize.y;

	drawBox(window, (AABB){0, 0, maxX, maxY});

	for(int x = 0; x < gridDimensions.x; ++x) {
		mvwaddch(window, 0, (x + 1) * cellSize.x, ACS_TTEE);
		mvwaddch(window, (gridDimensions.y + 1) * cellSize.y,
				 (x + 1) * cellSize.x, ACS_BTEE);

		mvwvline(window, 1, (x + 1) * cellSize.x, 0,
				 (gridDimensions.y + 1) * cellSize.y - 1);

		wattron(window, A_BOLD);
		mvwprintw(window, cellSize.y / 2, (x + 1) * cellSize.x + cellSize.x / 2,
				  "%c", 'A' + x);
		wattroff(window, A_BOLD);
	}
	for(int y = 0; y < gridDimensions.y; ++y) {
		mvwaddch(window, (y + 1) * cellSize.y, maxX, ACS_RTEE);
		mvwaddch(window, (y + 1) * cellSize.y, 0, ACS_LTEE);

		mvwhline(window, (y + 1) * cellSize.y, 1, 0, maxX - 1);

		wattron(window, A_BOLD);
		mvwprintw(window, (y + 1) * cellSize.y + cellSize.y / 2, cellSize.x / 2,
				  "%2d", 1 + y);
		wattroff(window, A_BOLD);
	}
	for(int y = 0; y < gridDimensions.y; ++y) {
		for(int x = 0; x < gridDimensions.x; ++x) {
			mvwaddch(window, (y + 1) * cellSize.y, (x + 1) * cellSize.x,
					 ACS_PLUS);
		}
	}
}
AABB getSelection(WINDOW *window, Vector2 gridDimensions, AABB cells) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	cells.max.x += 1;
	cells.max.y += 1;

	cells.min.x *= cellSize.x;
	cells.min.y *= cellSize.y;
	cells.max.x *= cellSize.x;
	cells.max.y *= cellSize.y;

	cells.min.x += 1;
	cells.max.x -= 1;
	cells.max.y -= 1;
	if(cellSize.y > 1)
		cells.min.y += 1;

	return cells;
}
void drawShip(WINDOW *window, Ship *shipRef, Vector2 gridDimensions,
			  Ship *ships, bool drawOutline) {
	Ship ship = *shipRef;
	ship.x += 1;
	ship.y += 1;
	Vector2 cellSize = getGridCellSize(window, gridDimensions);

	AABB shipCells =
		getSelection(window, gridDimensions, getOccupiedCells(ship));

	int color =
		isValidShipMove(ships, getGridBounds(gridDimensions), shipRef, shipRef)
			? getShipTypeColor(ship.type)
			: COLOR_INVALID;

	drawFilledBox(window, shipCells, color, drawOutline);
	wattron(window, COLOR_PAIR(color));
	mvwaddch(window, ship.y * cellSize.y + cellSize.y / 2,
			 ship.x * cellSize.x + cellSize.x / 2, ship.type + '1');
	wattroff(window, COLOR_PAIR(color));
}

void drawShips(WINDOW *window, Ship *ships, Vector2 gridDimensions,
			   int highlightedShip) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		Ship *ship = &ships[i];
		drawShip(window, ship, gridDimensions, ships, i == highlightedShip);
	}
}
void drawCursor(
	WINDOW *window,
	Vector2 gridDimensions, // NOLINT(bugprone-easily-swappable-parameters)
	Cursor cursor) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	mvwaddch(window, (cursor.y + 1) * cellSize.y + cellSize.y / 2,
			 (cursor.x + 1) * cellSize.x + cellSize.x / 2, 'x');
}
AABB indexToAABB(int index, int width) {
	Vector2 location = {index % width + 1, index / width + 1};
	return (AABB){location, location};
}
void drawHits(WINDOW *window, Vector2 gridDimensions,
			  HitInfo hits[gridDimensions.x * gridDimensions.y]) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	// bool hitShips[SHIP_TYPES];
	const int gridSize = gridDimensions.x * gridDimensions.y;
	for(size_t i = 0; i < gridSize; ++i) {
		HitInfo *hit = &hits[i];
		const HitType type = hit->type;
		// if(hitShips[hit->hitShip->type])
		//	continue;
		switch(type) {
			case INVALID_HIT: break;
			case NO_HIT:
				drawFilledBox(
					window,
					getSelection(window, gridDimensions,
								 indexToAABB((int)i, gridDimensions.x)),
					COLOR_NO_HIT, false);
				break;
			case HIT:
				drawFilledBox(
					window,
					getSelection(window, gridDimensions,
								 indexToAABB((int)i, gridDimensions.x)),
					COLOR_HIT, false);
				break;
			case DESTROYED:
				// hitShips[hit->hitShip->type] = true;
				drawShip(window, hit->hitShip, gridDimensions, NULL, false);
				break;
			default: break;
		}
	}
}

int getGridCellSizeX(WINDOW *window, Vector2 gridDimensions) {
	return (getmaxx(window) - 1) / (gridDimensions.x + 1);
}
int getGridCellSizeY(WINDOW *window, Vector2 gridDimensions) {
	return (getmaxy(window) - 1) / (gridDimensions.y + 1);
}

Vector2 getGridCellSize(WINDOW *window, Vector2 gridDimensions) {
	return (Vector2){getGridCellSizeX(window, gridDimensions),
					 getGridCellSizeY(window, gridDimensions)};
}
