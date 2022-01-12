#ifndef SRC_EVENTS_ATTACKMODE_H
#define SRC_EVENTS_ATTACKMODE_H

#include "player.h"
#include "state.h"

StateType attackMode(StateType incomingType, Player *players,
					 int *currentPlayerIndex, int input);

#endif // SRC_EVENTS_ATTACKMODE_H