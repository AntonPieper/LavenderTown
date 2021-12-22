#include "grid.h"
#include <ncurses.h>

int main() {
  initscr(); /* Start curses mode 		  */
  WINDOW *gridWindow =
      newwin(GRID_LINES * 2 + 3, GRID_COLUMNS * 4 + 3 + 1 + 1, 0, 0);
  refresh();
  drawGrid(gridWindow);
  getch();  /* Wait for user input */
  endwin(); /* End curses mode		  */

  return 0;
}
