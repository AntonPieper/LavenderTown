#include "drawSwitchAttackingPlayer.h"
#include "events/attackMode/drawAttackPlayer.h"
#include "playerWindows.h"
#include "util/drawing.h"

StateType drawSwitchAttackingPlayer(StateType incomingType, Player *players,
									int currentPlayerIndex,
									PlayerWindows windows) {
	Player *const currentPlayer = &players[currentPlayerIndex];
	Player *const enemyPlayer = &players[1 - currentPlayerIndex];

	eraseAllWindows(&windows);

	drawNameInCenter(windows.name, currentPlayer->name);

	drawPlayerBoard(currentPlayer, windows.primary, enemyPlayer,
					windows.tracking);

	drawStats(windows.info, currentPlayer->currentShip, currentPlayer->cursor);

	overwriteMainWindow(&windows);
	wrefresh(windows.main);

	return SWITCH_ATTACKING_PLAYER;
}