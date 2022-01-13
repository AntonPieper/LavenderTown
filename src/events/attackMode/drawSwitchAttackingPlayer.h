#ifndef SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER
#define SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER

#include "player.h"
#include "state.h"
#include <curses.h>

StateType drawSwitchAttackingPlayer(StateType incomingType, Player *players,
									int currentPlayerIndex, WINDOW *enemyWindow,
									WINDOW *gridWindow, WINDOW *nameWindow,
									WINDOW *infoWindow);

#endif // SRC_EVENTS_ATTACKMODE_DRAWSWITCHATTACKINGPLAYER