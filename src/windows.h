#ifndef SRC_WINDOWS_H
#define SRC_WINDOWS_H

#include <curses.h>

typedef struct PlayerWindows {
	WINDOW *main, *name, *info, *primary, *tracking;
} PlayerWindows;

void overwriteMainWindow(PlayerWindows *windows);

void eraseAllWindows(PlayerWindows *windows);

#endif // SRC_WINDOWS_H