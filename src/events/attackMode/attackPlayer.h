#ifndef SRC_EVENTS_ATTACKMODE_ATTACKPLAYER_H
#define SRC_EVENTS_ATTACKMODE_ATTACKPLAYER_H

#include "player.h"
#include "state.h"

StateType attackPlayer(StateType incomingType, Player *players,
					   int currentPlayerIndex);

#endif // SRC_EVENTS_ATTACKMODE_ATTACKPLAYER_H