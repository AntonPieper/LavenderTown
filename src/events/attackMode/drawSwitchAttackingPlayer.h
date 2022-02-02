#ifndef SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER
#define SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER

#include "player.h"
#include "playerWindows.h"
#include "state.h"
#include <curses.h>

StateType drawSwitchAttackingPlayer(StateType incomingType, Player *players,
									int currentPlayerIndex,
									PlayerWindows windows);

#endif // SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER