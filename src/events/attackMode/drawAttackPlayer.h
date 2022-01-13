#ifndef SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H
#define SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H

#include "player.h"
#include "state.h"
#include <curses.h>

void drawPlayerBoard(Player *currentPlayer, WINDOW *primaryWindow,
					 Player *enemyPlayer, WINDOW *secondaryWindow);

StateType drawAttackPlayer(StateType incomingType, Player *players,
						   int currentPlayerIndex, WINDOW *enemyWindow,
						   WINDOW *gridWindow, WINDOW *nameWindow,
						   WINDOW *infoWindow);

#endif // SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H