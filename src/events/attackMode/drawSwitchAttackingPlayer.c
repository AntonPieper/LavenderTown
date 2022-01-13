#include "drawSwitchAttackingPlayer.h"
#include "drawing.h"
#include "events/attackMode/drawAttackPlayer.h"

StateType drawSwitchAttackingPlayer(
	StateType incomingType, Player *players, int currentPlayerIndex,
	WINDOW *enemyWindow, // NOLINT(bugprone-easily-swappable-parameters)
	WINDOW *gridWindow, WINDOW *nameWindow, WINDOW *infoWindow) {
	Player *const currentPlayer = &players[currentPlayerIndex];
	Player *const enemyPlayer = &players[1 - currentPlayerIndex];

	werase(enemyWindow);
	werase(gridWindow);
	werase(nameWindow);
	werase(infoWindow);

	drawNameInCenter(nameWindow, currentPlayer->name);

	drawPlayerBoard(currentPlayer, gridWindow, enemyPlayer, enemyWindow);

	drawStats(infoWindow, currentPlayer->currentShip, currentPlayer->cursor);

	wrefresh(infoWindow);
	wrefresh(enemyWindow);
	wrefresh(gridWindow);
	wrefresh(nameWindow);

	return SWITCH_ATTACKING_PLAYER;
}