#ifndef SRC_EVENTS_ARRANGEMODE_ARRANGESHIPS_H
#define SRC_EVENTS_ARRANGEMODE_ARRANGESHIPS_H

#include "player.h"
#include "state.h"

StateType arrangeShips(StateType incomingType, Player *players,
					   int *currentPlayerIndex);

#endif // SRC_EVENTS_ARRANGEMODE_ARRANGESHIPS_H