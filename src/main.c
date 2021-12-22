#include <ncurses.h>

const int GRID_LINES = 10;
const int GRID_COLUMNS = 10;

int main() {
  initscr(); /* Start curses mode 		  */
  WINDOW *gridView =
      newwin(GRID_LINES * 2 + 3, GRID_COLUMNS * 4 + 3 + 1 + 1, 0, 0);
  refresh();
  box(gridView, 0, 0);
  for (int i = 0; i < 10; ++i) {
    mvwaddch(gridView, 0, i * 4 + 4, ACS_TTEE);
    mvwaddch(gridView, i * 2 + 2, GRID_COLUMNS * 4 + 4, ACS_RTEE);
    mvwaddch(gridView, GRID_COLUMNS * 2 + 2, i * 4 + 4, ACS_BTEE);
    mvwaddch(gridView, i * 2 + 2, 0, ACS_LTEE);
    whline(gridView, 0, GRID_COLUMNS * 4 + 3);
    mvwvline(gridView, 1, i * 4 + 4, 0, GRID_LINES * 2 + 1);

    mvwprintw(gridView, i * 2 + 3, 2, "%c", 'A' + i);
    mvwprintw(gridView, 1, i * 4 + 5, "%2d", 1 + i);
  }
  for (int y = 0; y < GRID_LINES; ++y)
    for (int x = 0; x < GRID_LINES; ++x) {
      mvwaddch(gridView, y * 2 + 2, x * 4 + 4, ACS_PLUS);
    }
  /*printw(
         "____________________________________________\n"
         "|  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n"
         "| A|   |   |   |   |   |   |   |   |   |   |\n"
         "| B|   |   |   |   |   |   |   |   |   |   |\n"
         "| C|   |   |   |   |   |   |   |   |   |   |\n"
         "| D|   |   |   |   |   |   |   |   |   |   |\n"
         "| E|   |   |   |   |   |   |   |   |   |   |\n"
         "| F|   |   |   |   |   |   |   |   |   |   |\n"
         "| G|   |   |   |   |   |   |   |   |   |   |\n"
         "| H|   |   |   |   |   |   |   |   |   |   |\n"
         "| I|   |   |   |   |   |   |   |   |   |   |\n"
         "| J|   |   |   |   |   |   |   |   |   |   |\n"
         "--------------------------------------------\n");*/

  wrefresh(gridView); /* Print it on to the real screen */
  getch();            /* Wait for user input */
  endwin();           /* End curses mode		  */

  return 0;
}
