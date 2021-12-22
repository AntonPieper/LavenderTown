#include "grid.h"

void drawGrid(WINDOW *gridWindow) {
  box(gridWindow, 0, 0);
  for (int i = 0; i < 10; ++i) {
    mvwaddch(gridWindow, 0, i * 4 + 4, ACS_TTEE);
    mvwaddch(gridWindow, i * 2 + 2, GRID_COLUMNS * 4 + 4, ACS_RTEE);
    mvwaddch(gridWindow, GRID_COLUMNS * 2 + 2, i * 4 + 4, ACS_BTEE);
    mvwaddch(gridWindow, i * 2 + 2, 0, ACS_LTEE);
    whline(gridWindow, 0, GRID_COLUMNS * 4 + 3);
    mvwvline(gridWindow, 1, i * 4 + 4, 0, GRID_LINES * 2 + 1);

    mvwprintw(gridWindow, i * 2 + 3, 2, "%c", 'A' + i);
    mvwprintw(gridWindow, 1, i * 4 + 5, "%2d", 1 + i);
  }
  for (int y = 0; y < GRID_LINES; ++y)
    for (int x = 0; x < GRID_LINES; ++x) {
      mvwaddch(gridWindow, y * 2 + 2, x * 4 + 4, ACS_PLUS);
    }

  wrefresh(gridWindow);
}