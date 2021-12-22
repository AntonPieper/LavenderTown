#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include <curses.h>

#define GRID_LINES 10
#define GRID_COLUMNS 10

void drawGrid(WINDOW *gridWindow);

#endif // SRC_GRID_H_