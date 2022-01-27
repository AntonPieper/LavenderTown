#ifndef SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H
#define SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H

#include "player.h"
#include "state.h"
#include "windows.h"
#include <curses.h>

void drawPlayerBoard(Player *currentPlayer, WINDOW *primaryWindow,
					 Player *enemyPlayer, WINDOW *trackingWindow);

StateType drawAttackPlayer(StateType incomingType, Player *players,
						   int currentPlayerIndex, PlayerWindows windows);

#endif // SRC_EVENTS_ATTACKMODE_DRAWATTACKPLAYER_H