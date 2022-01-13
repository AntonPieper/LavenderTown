#include "events/attackMode/switchAttackingPlayer.h"
#include "events/switchPlayer.h"
#include "input.h"
#include "state.h"

static const int ONE_SECOND = 1000;

StateType switchAttackingPlayer(StateType incomingType, Player players[],
								int *currentPlayerIndex) {
	if(incomingType == ATTACK_MODE)
		return DRAW_ATTACK_MODE;
	if(getInput(ONE_SECOND)) {
		return switchPlayerFullScreen(DRAW_ATTACK_MODE, players,
									  currentPlayerIndex);
	}
	return SWITCH_ATTACKING_PLAYER;
}