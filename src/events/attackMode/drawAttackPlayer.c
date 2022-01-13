#include "events/attackMode/drawAttackPlayer.h"
#include "drawing.h"

void drawPlayerBoard(Player *currentPlayer, WINDOW *primaryWindow,
					 Player *enemyPlayer, WINDOW *secondaryWindow) {
	drawGrid(secondaryWindow, currentPlayer->gridDimensions);
	drawHitMarkers(secondaryWindow, currentPlayer->gridDimensions,
				   enemyPlayer->hits);
	drawHitMarkers(primaryWindow, enemyPlayer->gridDimensions,
				   currentPlayer->hits);
	drawShips(secondaryWindow, currentPlayer->ships,
			  currentPlayer->gridDimensions, -1);

	drawGrid(primaryWindow, enemyPlayer->gridDimensions);

	drawHitShips(primaryWindow, enemyPlayer->gridDimensions,
				 currentPlayer->hits);
}

StateType drawAttackPlayer(
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

	drawCursor(gridWindow, currentPlayer->gridDimensions,
			   currentPlayer->cursor);
	drawStats(infoWindow, currentPlayer->currentShip, currentPlayer->cursor);

	wrefresh(infoWindow);
	wrefresh(enemyWindow);
	wrefresh(gridWindow);
	wrefresh(nameWindow);

	return ATTACK_MODE;
}