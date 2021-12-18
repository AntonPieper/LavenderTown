#include <curses.h>
#include <string.h>

const int GREET_COLOR = 1;
const int NAME_INPUT_COLOR = 2;

int main() {
  WINDOW *window = initscr();
  if (has_colors() == FALSE) {
    endwin();
    printf("Your Terminal does not support color!\n");
    exit(1);
  }
  start_color();
  init_pair(GREET_COLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(NAME_INPUT_COLOR, COLOR_MAGENTA, COLOR_BLACK);
  int rows, columns;
  // A Macro for (rows = getmaxx(window), columns=getmaxy(window))
  getmaxyx(window, rows, columns);
  printw("Hello World %s!", "from me"); // Works just like printf(...)
  char message[] = "Hello World from center of screen";
  mvprintw(rows / 2, (columns - strlen(message)) / 2, message);
  refresh();

  char name[64];
  mvaddstr(rows - 2, columns / 2 - 5, "Your name?");
  mvaddstr(rows - 1, columns / 2 - 5, "> ");

  attron(COLOR_PAIR(NAME_INPUT_COLOR) | A_ITALIC);
  getnstr(name, 63);
  attroff(COLOR_PAIR(NAME_INPUT_COLOR) | A_ITALIC);

  move(rows - 2, 0);
  clrtobot();

  char greeting[] = "Your name is ";
  move(rows / 2 + 1, (columns - strlen(greeting) - strlen(name)) / 2);
  printw("%s", greeting);
  attron(COLOR_PAIR(GREET_COLOR) | A_BOLD);
  printw("%s", name);
  attroff(COLOR_PAIR(GREET_COLOR) | A_BOLD);
  refresh();

  getch();
  endwin();

  return 0;
}
