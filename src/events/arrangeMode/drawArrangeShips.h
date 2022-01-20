#ifndef SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H
#define SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H

#include "player.h"
#include "state.h"
#include "util/drawing.h"

StateType drawArrangeShips(StateType incomingType, Player *players,
						   int currentPlayerIndex, WINDOW *enemyWindow,
						   WINDOW *gridWindow, WINDOW *nameWindow,
						   WINDOW *infoWindow);

#endif // SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H