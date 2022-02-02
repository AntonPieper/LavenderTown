#ifndef SRC_PLAYERWINDOWS_H
#define SRC_PLAYERWINDOWS_H

#include <curses.h>

typedef struct PlayerWindows {
	WINDOW *main, *name, *info, *primary, *tracking;
} PlayerWindows;

void overwriteMainWindow(PlayerWindows *windows);

void eraseAllWindows(PlayerWindows *windows);

#endif // SRC_PLAYERWINDOWS_H