#include "drawing.h"
#include "cursor.h"
#include "ship.h"
#include "vector.h"
#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int BYTE = 8;

void drawBox(WINDOW *window, AABB aabb) {
	WINDOW *borderBox =
		derwin(window, aabb.max.y - aabb.min.y + 1, aabb.max.x - aabb.min.x + 1,
			   aabb.min.y, aabb.min.x);
	box(borderBox, 0, 0);
	delwin(borderBox);
}

void drawFilledBox(WINDOW *window, AABB aabb, int attributes,
				   bool drawOutline) {
	const int dx = aabb.max.x - aabb.min.x + 1;
	const int dy = aabb.max.y - aabb.min.y + 1;
	WINDOW *filledBox = derwin(window, dy, dx, aabb.min.y, aabb.min.x);
	// wrefresh(window)
	wbkgd(filledBox, attributes);
	if(aabb.min.x == aabb.max.x)
		mvwvline(filledBox, 0, 0, ' ', dy);
	else if(aabb.min.y == aabb.max.y)
		mvwhline(filledBox, 0, 0, ' ', dx);
	if(drawOutline)
		wborder(filledBox, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD,
				ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD);
	delwin(filledBox);
}
void drawBorder(WINDOW *window, AABB aabb, chtype charType) {
	WINDOW *borderBox =
		derwin(window, aabb.max.y - aabb.min.y + 1, aabb.max.x - aabb.min.x + 1,
			   aabb.min.y, aabb.min.x);
	wborder(borderBox, charType, charType, charType, charType, charType,
			charType, charType, charType);
	delwin(borderBox);
}

void drawGrid(WINDOW *window, Vector2 gridDimensions) {
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);
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
		mvwprintw(window, (y + 1) * cellSize.y + cellSize.y / 2,
				  (cellSize.x - 1) / 2, "%2d", 1 + y);
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
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);
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
			  Ship *ships, bool drawOutline, bool drawPivot) {
	Ship ship = *shipRef;
	drawOutline ^= ship.sunk;
	ship.x += 1;
	ship.y += 1;
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);

	AABB shipCells =
		getSelection(window, gridDimensions, getOccupiedCells(ship));

	int attributes = COLOR_PAIR(
		isValidShipMove(ships, getGridBounds(gridDimensions), shipRef, shipRef)
			? getShipTypeColor(ship.type)
			: COLOR_INVALID);

	drawFilledBox(window, shipCells, attributes, drawOutline);
	if(!drawPivot)
		return;
	const Vector2 pivotLocation = {ship.x * cellSize.x + cellSize.x / 2,
								   ship.y * cellSize.y + cellSize.y / 2};
	bool pivotLocationAlreadyOccupied =
		(mvwinch(window, pivotLocation.y, pivotLocation.x) & A_CHARTEXT) != ' ';
	if(pivotLocationAlreadyOccupied)
		attributes |= A_BOLD;
	wattron(window, attributes);
	mvwaddch(window, pivotLocation.y, pivotLocation.x, ship.type + '1');
	wattroff(window, attributes);
}

void drawShips(WINDOW *window, Ship *ships, Vector2 gridDimensions,
			   int highlightedShip) {
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);
	for(int i = 0; i < SHIP_TYPES; ++i) {
		Ship *ship = &ships[i];
		drawShip(window, ship, gridDimensions, ships, i == highlightedShip,
				 highlightedShip != -2);
	}
}
AABB posToAABB(Vector2 pos) {
	++pos.x;
	++pos.y;
	return (AABB){pos, pos};
}
void drawCursor(
	WINDOW *window,
	Vector2 gridDimensions, // NOLINT(bugprone-easily-swappable-parameters)
	Cursor cursor) {
	Vector2 cellSize = getGridCellSize(window, gridDimensions);
	Vector2 drawLocation = {(cursor.x + 1) * cellSize.x + cellSize.x / 2,
							(cursor.y + 1) * cellSize.y + cellSize.y / 2};
	const unsigned int existingChar =
		mvwinch(window, drawLocation.y, drawLocation.x);
	const unsigned int attributes = A_BOLD | existingChar & A_COLOR;
	unsigned int cursorChar = existingChar & A_CHARTEXT;
	char cursorString[] = "▓";
	/*if(cursorChar - '1' <= 4) {
		cursorString[0] = (char)cursorChar;
		cursorString[1] = '\0';
	}*/
	drawBorder(window, getSelection(window, gridDimensions, posToAABB(cursor)),
			   ' ' | attributes);
	wattron(window, attributes);
	mvwaddstr(window, drawLocation.y, drawLocation.x, cursorString);
	wattroff(window, attributes);
}
void drawNameInCenter(WINDOW *window, char name[]) {
	const int rows = getmaxy(window);
	const int columns = getmaxx(window);
	mvwprintw(window, rows / 2, (columns - (int)strlen(name)) / 2, "%s", name);
}
void drawStats(WINDOW *window, ShipType shipType, Cursor cursor) {
	char *shipName = getShipTypeName(shipType);
	mvwaddstr(window, 0, 0, "cursor: ");
	wattron(window, A_BOLD);
	wprintw(window, "%c%d", cursor.x + 'A', cursor.y + 1);
	wattroff(window, A_BOLD);
	waddstr(window, ", current ship: ");
	int color = getShipTypeColor(shipType);
	wattron(window, COLOR_PAIR(color));
	wprintw(window, "%s", shipName);
	wattroff(window, COLOR_PAIR(color));
}

AABB indexToAABB(int index, int width) {
	Vector2 location = {index % width, index / width};
	return posToAABB(location);
}

void drawHitShips(WINDOW *window, Vector2 gridDimensions,
				  HitInfo hits[gridDimensions.x * gridDimensions.y]) {
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);
	const size_t hitSHipsLength = (SHIP_TYPES + BYTE / 2) / BYTE;
	uint_fast8_t hitShips[hitSHipsLength];
	memset(hitShips, 0, hitSHipsLength * sizeof(*hitShips));
	const int gridSize = gridDimensions.x * gridDimensions.y;
	for(size_t i = 0; i < gridSize; ++i) {
		const HitInfo *hit = &hits[i];
		if(hit->type != DESTROYED)
			continue;
		const ShipType type = hit->hitShip->type;
		if(hit->type != DESTROYED ||
		   hitShips[type / BYTE] & (1 << (type % BYTE)))
			continue;

		hitShips[type / BYTE] |= (1 << (type % BYTE));
		drawShip(window, hit->hitShip, gridDimensions, NULL, true, false);
	}
}

void drawHitMarkers(WINDOW *window, Vector2 gridDimensions,
					HitInfo hits[gridDimensions.x * gridDimensions.y]) {
	const Vector2 cellSize = getGridCellSize(window, gridDimensions);
	const char hitChar = cellSize.y > 1 ? 'X' : 'x';
	for(int y = 0; y < gridDimensions.y; ++y)
		for(int x = 0; x < gridDimensions.x; ++x) {
			HitInfo hit = {0};
			hit = hits[getIndex(x, y, gridDimensions.x)];
			const HitType type = hit.type;
			if(type == NO_HIT)
				wattron(window, COLOR_PAIR(COLOR_NO_HIT));
			else if(type == HIT)
				wattron(window, COLOR_PAIR(COLOR_HIT));
			if(type != INVALID_HIT)
				mvwaddch(window, (y + 1) * cellSize.y + cellSize.y / 2,
						 (x + 1) * cellSize.x + cellSize.x / 2, hitChar);
			wattroff(window, A_COLOR);
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
