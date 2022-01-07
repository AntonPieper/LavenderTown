#include "events/arrangeShips.h"
#include "input.h"
#include "player.h"
#include "ship.h"
#include "state.h"
#include <ctype.h>
#include <curses.h>

static const KeyMapping FORWARD[] = {'w', 1,  KEY_UP,   1,  'k', 1,
									 's', -1, KEY_DOWN, -1, 'j', -1};
static const size_t FORWARD_LENGTH = sizeof(FORWARD) / sizeof(FORWARD[0]);

static const KeyMapping RIGHT[] = {'d', 1,  KEY_RIGHT, 1,  'l', 1,
								   'a', -1, KEY_LEFT,  -1, 'h', -1};
static const size_t RIGHT_LENGTH = sizeof(RIGHT) / sizeof(RIGHT[0]);

static const KeyMapping ROTATE_RIGHT[] = {'e', 1,  KEY_NEXT,     1,  'i', 1,
										  'q', -1, KEY_PREVIOUS, -1, 'u', -1};
static const size_t ROTATE_RIGHT_LENGTH =
	sizeof(ROTATE_RIGHT) / sizeof(ROTATE_RIGHT[0]);

static const KeyMapping GRAB_SHIP[] = {' ', 1, KEY_HOME, 1};
static const size_t GRAB_SHIP_LENGTH = sizeof(GRAB_SHIP) / sizeof(GRAB_SHIP[0]);

static const KeyMapping SWITCH_PLAYER[] = {'\n', 1, KEY_ENTER, 1};
static const size_t SWITCH_PLAYER_LENGTH =
	sizeof(GRAB_SHIP) / sizeof(GRAB_SHIP[0]);

StateType handleMovement(Player *player, Ship *currentShip, int dx, int dy);
StateType handleRotation(Player *player, Ship *currentShip, int rotateRight);
StateType handleSwitchShip(Player *player, int input);
StateType handleGrabShip(Player *player, Ship *currentShip);
StateType handleSwitchPlayers(Player players[2], int *currentPlayerIndex);

StateType arrangeShips(StateType incomingType, Player players[2],
					   int *currentPlayerIndex, int input) {
	input = tolower(input);
	Player *player = &players[*currentPlayerIndex];
	Ship *currentShip = &player->ships[player->currentShip];

	int forward = getMappedValue(FORWARD_LENGTH, FORWARD, input);
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

	if(getMappedValue(SWITCH_PLAYER_LENGTH, SWITCH_PLAYER, input))
		return handleSwitchPlayers(players, currentPlayerIndex);

	return ARRANGE_SHIPS;
}

StateType handleMovement(Player *player, Ship *currentShip, int dx, int dy) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.x += dx;
		newShip.y += dy;
		if(!shipInsideBounds(&newShip, getGridBounds(player->grid)))
			return ARRANGE_SHIPS;
		currentShip->x += dx;
		currentShip->y += dy;

		player->cursor.x = currentShip->x;
		player->cursor.y = currentShip->y;
	} else {
		Cursor newCursor = player->cursor;
		newCursor.x += dx;
		newCursor.y += dy;
		if(!cursorInsideBounds(newCursor, getGridBounds(player->grid)))
			return ARRANGE_SHIPS;
		player->currentShip = getShipIndexAtPosition(newCursor, player->ships);
		player->cursor.x += dx;
		player->cursor.y += dy;
	}
	return DRAW_ARRANGE_SHIPS;
}
StateType handleRotation(Player *player, Ship *currentShip, int rotateRight) {
	if(player->isHoldingShip) {
		Ship newShip = *currentShip;
		newShip.orientation = (newShip.orientation + rotateRight) % DIRECTIONS;
		if(shipInsideBounds(&newShip, getGridBounds(player->grid)))
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
		if(!isValidShipMove(player->ships, getGridBounds(player->grid),
							currentShip, currentShip))
			return ARRANGE_SHIPS;
		player->isHoldingShip = false;
		return DRAW_ARRANGE_SHIPS;
	}
	int foundShip = getShipIndexAtPosition(player->cursor, player->ships);
	if(foundShip != -1) {
		selectShip(player, foundShip);
		player->isHoldingShip = true;
		return DRAW_ARRANGE_SHIPS;
	}
	return ARRANGE_SHIPS;
}
StateType handleSwitchPlayers(Player players[2], int *currentPlayerIndex) {
	++*currentPlayerIndex;
	if(*currentPlayerIndex > 1) {
		*currentPlayerIndex = 0;
		return DRAW_ATTACK_MODE;
	}
	return DRAW_ARRANGE_SHIPS;
}