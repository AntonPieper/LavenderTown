#ifndef SRC_EVENTS_DRAWARRANGESHIPS_H
#define SRC_EVENTS_DRAWARRANGESHIPS_H

#include "drawing.h"
#include "player.h"
#include "state.h"

StateType drawArrangeShips(StateType incomingType, Player *currentPlayer,
						   WINDOW *grid, WINDOW *name, WINDOW *info);

#endif // SRC_EVENTS_DRAWARRANGESHIPS_H