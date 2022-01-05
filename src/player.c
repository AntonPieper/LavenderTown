#include "player.h"
#include "aabb.h"
#include "grid.h"
#include "ship.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

Player createPlayer(char *name, Grid *grid) {
	Player player = {0};
	player.name = name;
	player.grid = grid;
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

void selectShip(Player *player, Ship *shipToSelect) {
	if(shipToSelect != NULL) {
		player->currentShip = shipToSelect;
		player->isHoldingShip = true;
	}
}

void deselectShip(Player *player) { player->isHoldingShip = false; }

void handleResize(Player *player);
void handleMovement(Player *player, Grid *grid, Ship *currentShip, int dx,
					int dy);
void handleRotateLeft(Player *player, Grid *grid, Ship *currentShip);
void handleRotateRight(Player *player, Grid *grid, Ship *currentShip);
void handleShipSelection(Player *player, Grid *grid, int input);
void handleHoldingShip(Player *player, Grid *grid, Ship *currentShip);
void handleQuit();

void handleInput(Player *player, int input) {
	Ship *currentShip = player->currentShip;
	Grid *grid = player->grid;
	switch(input) {
		case ERR: return;
		case KEY_RESIZE: return handleResize(player);
		case 'W':
		case 'w':
		case 'k':
		case 'K':
		case KEY_UP: return handleMovement(player, grid, currentShip, 0, -1);
		case 'S':
		case 's':
		case 'J':
		case 'j':
		case KEY_DOWN: return handleMovement(player, grid, currentShip, 0, 1);
		case 'A':
		case 'a':
		case 'H':
		case 'h':
		case KEY_LEFT: return handleMovement(player, grid, currentShip, -1, 0);
		case 'D':
		case 'd':
		case 'L':
		case 'l':
		case KEY_RIGHT: return handleMovement(player, grid, currentShip, 1, 0);
		case 'U':
		case 'u':
		case 'Q':
		case 'q':
		case KEY_PREVIOUS: return handleRotateLeft(player, grid, currentShip);
		case 'I':
		case 'i':
		case 'E':
		case 'e':
		case KEY_NEXT: return handleRotateRight(player, grid, currentShip);
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': return handleShipSelection(player, grid, input);
		case ' ':
		case KEY_HOME: return handleHoldingShip(player, grid, currentShip);
		case '\n':
		case KEY_ENTER:
		case KEY_EXIT:
		case KEY_CANCEL: return handleQuit();
		default: return;
	}
}

void handleResize(Player *player) { player->requestsRedraw = true; }
void handleMovement(Player *player, Grid *grid, Ship *currentShip, int dx,
					int dy) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.x += dx;
		newShip.y += dy;
		if(isInsideBounds(&newShip, grid)) {
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
	player->requestsRedraw = true;
}

void handleRotateLeft(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation + 1) % ORIENTATIONS;
		if(isInsideBounds(&newShip, grid))
			currentShip->orientation = newShip.orientation;
		player->requestsRedraw = true;
	}
}
void handleRotateRight(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation - 1) % ORIENTATIONS;
		if(isInsideBounds(&newShip, grid))
			currentShip->orientation = newShip.orientation;
		player->requestsRedraw = true;
	}
}
void handleShipSelection(Player *player, Grid *grid, int input) {
	selectShip(player, &grid->ships[input - '1']);
	player->requestsRedraw = true;
}
void handleHoldingShip(Player *player, Grid *grid, Ship *currentShip) {
	if(player->isHoldingShip) {
		if(isValidMove(grid, currentShip, currentShip)) {
			player->isHoldingShip = false;
			player->requestsRedraw = true;
		}
	} else {
		Ship *foundShip =
			getShipAtPosition(player->cursor, grid->ships, SHIP_TYPES);
		if(foundShip != 0) {
			selectShip(player, foundShip);
			player->isHoldingShip = true;
			player->requestsRedraw = true;
		}
	}
}
void handleQuit() {
	endwin();
	exit(0);
}