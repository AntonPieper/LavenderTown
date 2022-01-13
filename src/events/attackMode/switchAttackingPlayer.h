#ifndef SRC_EVENTS_ATTACKMODE_SWITCHATTACKINGPLAYER
#define SRC_EVENTS_ATTACKMODE_SWITCHATTACKINGPLAYER

#include "player.h"
#include "state.h"

StateType switchAttackingPlayer(StateType incomingType, Player players[],
								int *currentPlayerIndex);

#endif // SRC_EVENTS_ATTACKMODE_SWITCHATTACKINGPLAYER