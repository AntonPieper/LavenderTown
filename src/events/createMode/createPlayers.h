#ifndef SRC_EVENTS_CREATEMODE_CREATEPLAYERS_H
#define SRC_EVENTS_CREATEMODE_CREATEPLAYERS_H

#include "player.h"
#include "state.h"

StateType createPlayers(StateType incomingType, Player players[2],
						int *currentPlayerIndex);

#endif // SRC_EVENTS_CREATEMODE_CREATEPLAYERS_H