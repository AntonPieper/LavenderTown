#ifndef SRC_EVENTS_DRAWATTACKMODE_H
#define SRC_EVENTS_DRAWATTACKMODE_H

#include "player.h"
#include "state.h"
#include <curses.h>

StateType drawAttackMode(StateType incomingType, Player *players,
						 int currentPlayerIndex, WINDOW *window);

#endif // SRC_EVENTS_DRAWATTACKMODE_H