#include "player.h"
#include "aabb.h"
#include "grid.h"
#include "ship.h"
#include "vector.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Player createPlayer(char *name, Grid *grid, Ship *ships) {
	Player player = {0};
	player.name = name;
	player.grid = grid;
	memcpy(player.ships, ships, sizeof(Ship) * SHIP_TYPES);
	return player;
}

const int MAX_PLAYER_NAME_LENGTH = 64;

const char ENTER_YOUR_NAME_MESSAGE[] = "Enter your name: ";

char *getPlayerName(WINDOW *window) {
	mvwprintw(window, getmaxy(window) / 2,
			  (getmaxx(window) - (int)strlen(ENTER_YOUR_NAME_MESSAGE)) / 2,
			  ENTER_YOUR_NAME_MESSAGE);
	char *name = malloc((MAX_PLAYER_NAME_LENGTH + 1) * sizeof(char));
	wrefresh(window);
	wgetnstr(window, name, MAX_PLAYER_NAME_LENGTH);
	return name;
}

void selectShip(Player *player, int index) {
	if(index > -1 && index < SHIP_TYPES) {
		player->currentShip = index;
		player->isHoldingShip = true;
	}
}

void deselectShip(Player *player) { player->isHoldingShip = false; }

State handleResize();
State handleMovement(Player *player, Grid *grid, Ship *currentShip, int dx,
					 int dy);
State handleRotateLeft(Player *player, Grid *grid, Ship *currentShip);
State handleRotateRight(Player *player, Grid *grid, Ship *currentShip);
State handleShipSelection(Player *player, int input);
State handleHoldingShip(Player *player, Grid *grid, Ship *currentShip);
State handleNextStep();
State handleQuit();

State handleInput(Player *player, int input) {
	Ship *currentShip = &player->ships[player->currentShip];
	Grid *grid = player->grid;
	input = tolower(input);
	switch(input) {
		case ERR: return IDLE;
		case KEY_RESIZE: return handleResize(player);
		case 'w':
		case 'k':
		case KEY_UP: return handleMovement(player, grid, currentShip, 0, -1);
		case 's':
		case 'j':
		case KEY_DOWN: return handleMovement(player, grid, currentShip, 0, 1);
		case 'a':
		case 'h':
		case KEY_LEFT: return handleMovement(player, grid, currentShip, -1, 0);
		case 'd':
		case 'l':
		case KEY_RIGHT: return handleMovement(player, grid, currentShip, 1, 0);
		case 'u':
		case 'q':
		case KEY_PREVIOUS: return handleRotateLeft(player, grid, currentShip);
		case 'i':
		case 'e':
		case KEY_NEXT: return handleRotateRight(player, grid, currentShip);
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': return handleShipSelection(player, input);
		case ' ':
		case KEY_HOME: return handleHoldingShip(player, grid, currentShip);
		case '\n':
		case KEY_ENTER: return handleNextStep();
		case KEY_EXIT:
		case KEY_CANCEL: return handleQuit();
		default: return IDLE;
	}
}

State handleResize() { return REQUEST_REDRAW; }
State handleMovement(Player *player, Grid *grid, Ship *currentShip, int dx,
					 int dy) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.x += dx;
		newShip.y += dy;
		if(isInsideBounds(&newShip, getGridBounds(grid))) {
			currentShip->x += dx;
			currentShip->y += dy;

			player->cursor.x = currentShip->x;
			player->cursor.y = currentShip->y;
		}
	} else {
		Vector2 newCursor = player->cursor;
		newCursor.x += dx;
		newCursor.y += dy;
		if(pointInside((AABB){0, 0, grid->size.x - 1, grid->size.y - 1},
					   newCursor)) {
			player->cursor.x += dx;
			player->cursor.y += dy;
		}
	}
	return REQUEST_REDRAW;
}

State handleRotateLeft(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation + 1) % ORIENTATIONS;
		if(isInsideBounds(&newShip, getGridBounds(grid)))
			currentShip->orientation = newShip.orientation;
		return REQUEST_REDRAW;
	}
	return IDLE;
}
State handleRotateRight(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation - 1) % ORIENTATIONS;
		if(isInsideBounds(&newShip, getGridBounds(grid)))
			currentShip->orientation = newShip.orientation;
		return REQUEST_REDRAW;
	}
	return IDLE;
}
State handleShipSelection(Player *player, int input) {
	selectShip(player, input - '1');
	return REQUEST_REDRAW;
}
State handleHoldingShip(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		if(isValidMove(player->ships, getGridBounds(grid), currentShip,
					   currentShip)) {
			player->isHoldingShip = false;
			return REQUEST_REDRAW;
		}
	} else {
		int foundShip =
			getShipIndexAtPosition(player->cursor, player->ships, SHIP_TYPES);
		if(foundShip != -1) {
			selectShip(player, foundShip);
			player->isHoldingShip = true;
			return REQUEST_REDRAW;
		}
	}
	return IDLE;
}
State handleNextStep() { return NEXT_STEP | REQUEST_REDRAW; }
State handleQuit() { return QUIT; }