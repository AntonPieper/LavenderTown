#include "events/attackMode/drawAttackPlayer.h"
#include "util/drawing.h"
#include "windows.h"

void drawPlayerBoard(Player *currentPlayer, WINDOW *primaryWindow,
					 Player *enemyPlayer, WINDOW *trackingWindow) {
	drawGrid(trackingWindow, currentPlayer->gridDimensions);
	drawHitMarkers(trackingWindow, currentPlayer->gridDimensions,
				   enemyPlayer->hits);
	drawShips(trackingWindow, currentPlayer->ships,
			  currentPlayer->gridDimensions, -1);
	drawHitMarkers(primaryWindow, enemyPlayer->gridDimensions,
				   currentPlayer->hits);

	drawGrid(primaryWindow, enemyPlayer->gridDimensions);

	drawHitShips(primaryWindow, enemyPlayer->gridDimensions,
				 currentPlayer->hits);
}

StateType drawAttackPlayer(StateType incomingType, Player *players,
						   int currentPlayerIndex, PlayerWindows windows) {
	Player *const currentPlayer = &players[currentPlayerIndex];
	Player *const enemyPlayer = &players[1 - currentPlayerIndex];

	eraseAllWindows(&windows);

	drawNameInCenter(windows.name, currentPlayer->name);
	drawPlayerBoard(currentPlayer, windows.primary, enemyPlayer,
					windows.tracking);

	drawCursor(windows.primary, currentPlayer->gridDimensions,
			   currentPlayer->cursor);
	drawStats(windows.info, currentPlayer->currentShip, currentPlayer->cursor);

	overwriteMainWindow(&windows);
	wrefresh(windows.main);

	return ATTACK_MODE;
}