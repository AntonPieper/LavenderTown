#ifndef SRC_EVENTS_SWITCH_PLAYER_H
#define SRC_EVENTS_SWITCH_PLAYER_H

#include "player.h"
#include "state.h"
#include <curses.h>

StateType switchPlayer(StateType incomingType, Player *players,
					   int *currentPlayerIndex, WINDOW *window);

StateType switchPlayerFullScreen(StateType incomingType, Player *players,
								 int *currentPlayerIndex);
#endif // SRC_EVENTS_SWITCH_PLAYER_H