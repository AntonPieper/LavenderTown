#ifndef SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H
#define SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H

#include "player.h"
#include "playerWindows.h"
#include "state.h"
#include "util/drawing.h"

StateType drawArrangeShips(StateType incomingType, Player *players,
						   int currentPlayerIndex, PlayerWindows windows);

#endif // SRC_EVENTS_ARRANGEMODE_DRAWARRANGESHIPS_H