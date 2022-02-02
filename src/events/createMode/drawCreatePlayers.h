#ifndef SRC_EVENTS_CREATEMODE_DRAWCREATEPLAYERS_H
#define SRC_EVENTS_CREATEMODE_DRAWCREATEPLAYERS_H

#include "player.h"
#include "playerWindows.h"
#include "state.h"
#include "util/drawing.h"

StateType drawCreatePlayers(StateType incomingType, Player *players,
							int playerIndex, PlayerWindows windows);

#endif // SRC_EVENTS_CREATEMODE_DRAWCREATEPLAYERS_H