#include "events/drawAttackMode.h"
#include "drawing.h"

StateType drawAttackMode(StateType incomingType, Player *players,
						 int currentPlayerIndex, WINDOW *window) {
	Player *const currentPlayer = &players[currentPlayerIndex];
	werase(window);
	drawGrid(window, currentPlayer->gridDimensions);

	drawHits(window, currentPlayer->gridDimensions, currentPlayer->hits);

	drawCursor(window, currentPlayer->gridDimensions, currentPlayer->cursor);
	return ATTACK_MODE;
}