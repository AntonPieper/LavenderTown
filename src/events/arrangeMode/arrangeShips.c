#include "events/arrangeMode/arrangeShips.h"
#include "input.h"
#include "player.h"
#include "ship.h"
#include "state.h"
#include <ctype.h>
#include <curses.h>
#include <stdbool.h>

static const KeyMapping UP[] = {'w', 1,  KEY_UP,   1,  'k', 1,
								's', -1, KEY_DOWN, -1, 'j', -1};
static const size_t UP_LENGTH = sizeof(UP) / sizeof(*UP);

static const KeyMapping RIGHT[] = {'d', 1,  KEY_RIGHT, 1,  'l', 1,
								   'a', -1, KEY_LEFT,  -1, 'h', -1};
static const size_t RIGHT_LENGTH = sizeof(RIGHT) / sizeof(*RIGHT);

static const KeyMapping ROTATE_RIGHT[] = {
	'e', 1,  KEY_NPAGE, 1,  KEY_NEXT,     1,  'i', 1,
	'q', -1, KEY_PPAGE, -1, KEY_PREVIOUS, -1, 'u', -1};
static const size_t ROTATE_RIGHT_LENGTH =
	sizeof(ROTATE_RIGHT) / sizeof(*ROTATE_RIGHT);

static const KeyMapping GRAB_SHIP[] = {' ', 1, KEY_HOME, 1};
static const size_t GRAB_SHIP_LENGTH = sizeof(GRAB_SHIP) / sizeof(*GRAB_SHIP);

static const KeyMapping NEXT_PLAYER[] = {'\n', 1, KEY_ENTER, 1};
static const size_t NEXT_PLAYER_LENGTH =
	sizeof(NEXT_PLAYER) / sizeof(*NEXT_PLAYER);

static const KeyMapping EXIT[] = {KEY_END, 1, 27, 1, 3, 1};
static const size_t EXIT_LENGTH = sizeof(EXIT) / sizeof(*EXIT);

StateType handleMovement(Player *player, Ship *currentShip, int dx, int dy);
StateType handleRotation(Player *player, Ship *currentShip, int rotateRight);
StateType handleSwitchShip(Player *player, int input);
StateType handleGrabShip(Player *player, Ship *currentShip);
StateType handleNextPlayer(Player players[2], int *currentPlayerIndex);

StateType arrangeShips(StateType incomingType, Player players[2],
					   int *currentPlayerIndex) {
	int input = tolower(getInput(-1));
	Player *player = &players[*currentPlayerIndex];
	Ship *currentShip = &player->ships[player->currentShip];

	int forward = getMappedValue(UP_LENGTH, UP, input);
	int right = getMappedValue(RIGHT_LENGTH, RIGHT, input);
	if(forward || right)
		return handleMovement(player, currentShip, right, -forward);

	int rotateRight = getMappedValue(ROTATE_RIGHT_LENGTH, ROTATE_RIGHT, input);
	if(rotateRight)
		return handleRotation(player, currentShip, rotateRight);

	if(input - '1' >= 0 && input - '1' <= 4) {
		return handleSwitchShip(player, input);
	}

	if(getMappedValue(GRAB_SHIP_LENGTH, GRAB_SHIP, input))
		return handleGrabShip(player, currentShip);

	if(getMappedValue(NEXT_PLAYER_LENGTH, NEXT_PLAYER, input))
		return handleNextPlayer(players, currentPlayerIndex);

	if(getMappedValue(EXIT_LENGTH, EXIT, input))
		return QUIT;

	return ARRANGE_SHIPS;
}

StateType handleMovement(Player *player, Ship *currentShip, int dx, int dy) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.x += dx;
		newShip.y += dy;
		if(!shipInsideBounds(&newShip, getGridBounds(player->gridDimensions)))
			return ARRANGE_SHIPS;
		currentShip->x += dx;
		currentShip->y += dy;

		player->cursor.x = currentShip->x;
		player->cursor.y = currentShip->y;
	} else {
		Cursor newCursor = player->cursor;
		newCursor.x += dx;
		newCursor.y += dy;
		if(!cursorInsideBounds(newCursor,
							   getGridBounds(player->gridDimensions)))
			return ARRANGE_SHIPS;
		player->currentShip = getShipTypeAtPosition(newCursor, player->ships);
		player->cursor.x += dx;
		player->cursor.y += dy;
	}
	return DRAW_ARRANGE_SHIPS;
}
StateType handleRotation(Player *player, Ship *currentShip, int rotateRight) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation + rotateRight) % DIRECTIONS;
		if(shipInsideBounds(&newShip, getGridBounds(player->gridDimensions)))
			currentShip->orientation = newShip.orientation;
		return DRAW_ARRANGE_SHIPS;
	}
	return ARRANGE_SHIPS;
}
StateType handleSwitchShip(Player *player, int input) {
	selectShip(player, input - '1');
	return DRAW_ARRANGE_SHIPS;
}
StateType handleGrabShip(Player *player, Ship *currentShip) {
	if(player->isHoldingShip) {
		if(!isValidShipMove(player->ships,
							getGridBounds(player->gridDimensions), currentShip,
							currentShip))
			return ARRANGE_SHIPS;
		player->isHoldingShip = false;
		return DRAW_ARRANGE_SHIPS;
	}
	int foundShip = getShipTypeAtPosition(player->cursor, player->ships);
	if(foundShip != -1) {
		selectShip(player, foundShip);
		player->isHoldingShip = true;
		return DRAW_ARRANGE_SHIPS;
	}
	return ARRANGE_SHIPS;
}
StateType handleNextPlayer(Player players[2], int *currentPlayerIndex) {
	players[*currentPlayerIndex].isHoldingShip = false;
	players[*currentPlayerIndex].currentShip = INVALID;
	++*currentPlayerIndex;
	if(*currentPlayerIndex > 1) {
		*currentPlayerIndex = 0;
		return DRAW_ATTACK_MODE;
	}
	return DRAW_ARRANGE_SHIPS;
}
