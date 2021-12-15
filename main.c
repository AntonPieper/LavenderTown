#include <ncurses.h>

int main() {
  const WINDOW *window = initscr();

  do {
    clear();
    int maxX = getmaxx(window);
    int maxY = getmaxy(window);
    for (int y = 0; y < maxY; ++y)
      for (int x = 0; x < maxX; ++x) {
        if (x % (maxX / 10) == 0 || y % (maxY / 10) == 0) mvaddch(y, x, '.');
      }
    refresh();
  } while (getch() == KEY_RESIZE);
  endwin();
  return 0;
}
