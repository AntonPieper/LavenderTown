#ifndef SRC_STATE_CREATEPLAYERS_H
#define SRC_STATE_CREATEPLAYERS_H

#include "player.h"
#include "state.h"

StateType createPlayers(StateType incomingType, Player players[2],
						int *currentPlayerIndex, int inputData);

#endif // SRC_STATE_CREATEPLAYERS_H