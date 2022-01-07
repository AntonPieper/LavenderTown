#ifndef SRC_EVENTS_ARRANGESHIPS_H
#define SRC_EVENTS_ARRANGESHIPS_H

#include "player.h"
#include "state.h"

StateType arrangeShips(StateType incomingType, Player *players,
					   int *currentPlayerIndex, int input);

#endif // SRC_EVENTS_ARRANGESHIPS_H