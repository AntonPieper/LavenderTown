#ifndef SRC_EVENTS_ENDSCREEN_ENDSCREEN_H
#define SRC_EVENTS_ENDSCREEN_ENDSCREEN_H

#include "player.h"
#include "playerWindows.h"
#include "state.h"

StateType endScreen(Player *players, int currentPlayerIndex,
					PlayerWindows windows);

#endif // SRC_EVENTS_ENDSCREEN_ENDSCREEN_H