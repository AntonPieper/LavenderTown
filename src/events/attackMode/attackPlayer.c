#include "events/attackMode/attackPlayer.h"
#include "input.h"
#include "player.h"
#include "ship.h"
#include "state.h"
#include <ctype.h>
#include <curses.h>
#include <stdint.h>

static const KeyMapping UP[] = {'w', 1,  KEY_UP,   1,  'k', 1,
								's', -1, KEY_DOWN, -1, 'j', -1};
static const size_t UP_LENGTH = sizeof(UP) / sizeof(UP[0]);

static const KeyMapping RIGHT[] = {'d', 1,  KEY_RIGHT, 1,  'l', 1,
								   'a', -1, KEY_LEFT,  -1, 'h', -1};
static const size_t RIGHT_LENGTH = sizeof(RIGHT) / sizeof(RIGHT[0]);

static const KeyMapping ATTACK[] = {'\n', 1, KEY_ENTER, 1, ' ', 1, KEY_HOME, 1};
static const size_t ATTACK_LENGTH = sizeof(ATTACK) / sizeof(ATTACK[0]);

static const KeyMapping EXIT[] = {KEY_END, 1, 27, 1, 3, 1};
static const size_t EXIT_LENGTH = sizeof(EXIT) / sizeof(EXIT[0]);

static StateType handleMovement(Player *players, int currentPlayerIndex,
								Ship *currentShip, int dx, int dy);
static StateType handleAttack(Player players[2], int currentPlayerIndex);

StateType attackPlayer(StateType incomingType, Player players[2],
					   int currentPlayerIndex) {
	int input = getInput(-1);
	if(input < INT8_MAX)
		input = tolower(input);
	Player *player = &players[currentPlayerIndex];
	Ship *currentShip = &player->ships[player->currentShip];

	int forward = getMappedValue(UP_LENGTH, UP, input);
	int right = getMappedValue(RIGHT_LENGTH, RIGHT, input);
	if(forward || right)
		return handleMovement(players, currentPlayerIndex, currentShip, right,
							  -forward);

	if(getMappedValue(ATTACK_LENGTH, ATTACK, input))
		return handleAttack(players, currentPlayerIndex);

	if(getMappedValue(EXIT_LENGTH, EXIT, input))
		return QUIT;

	return ATTACK_MODE;
}

static StateType handleMovement(Player *players, int currentPlayerIndex,
								Ship *currentShip, int dx, int dy) {
	Player *player = &players[currentPlayerIndex];
	Player *enemy = &players[1 - currentPlayerIndex];
	Cursor newCursor = player->cursor;
	newCursor.x += dx;
	newCursor.y += dy;
	if(!cursorInsideBounds(newCursor, getGridBounds(enemy->gridDimensions)))
		return ATTACK_MODE;
	ShipType newShipType = getShipTypeAtPosition(newCursor, enemy->ships);
	if(!enemy->ships[newShipType].sunk)
		newShipType = INVALID;
	player->currentShip = newShipType;
	player->cursor.x += dx;
	player->cursor.y += dy;
	return DRAW_ATTACK_MODE;
}
static StateType handleAttack(Player players[2], int currentPlayerIndex) {
	Player *player = &players[currentPlayerIndex];
	Player *enemy = &players[1 - currentPlayerIndex];

	int shotIndex =
		getIndex(player->cursor.x, player->cursor.y, player->gridDimensions.x);

	if(player->hits[shotIndex].type)
		return ATTACK_MODE;

	attack(player, player->cursor, enemy);

	const Ship *enemyShips = enemy->ships;

	bool isWinner = true;

	for(int i = 0; i < SHIP_TYPES; i++) {
		isWinner = isWinner && enemyShips[i].sunk;
	}
	if(isWinner) {
		return END_SCREEN;
	}
	return DRAW_SWITCH_ATTACKING_PLAYER;
}
