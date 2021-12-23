#include <ncurses.h>

struct setCoord {
  int y, x;
};

struct setCoord cursor;

int main() {
  initscr(); /* Start curses mode       */

  int x, y;

  cursor.y = 2;
  cursor.x = 3;
  clear();
  noecho();

  printw("________________________\n"
         "| |1|2|3|4|5|6|7|8|9|10|\n"
         "|A| | | | | | | | | |  |\n"
         "|B| | | | | | | | | |  |\n"
         "|C| | | | | | | | | |  |\n"
         "|D| | | | | | | | | |  |\n"
         "|E| | | | | | | | | |  |\n"
         "|F| | | | | | | | | |  |\n"
         "|G| | | | | | | | | |  |\n"
         "|H| | | | | | | | | |  |\n"
         "|I| | | | | | | | | |  |\n"
         "|J| | | | | | | | | |  |\n"
         "________________________\n");
  move(cursor.y, cursor.x);

  refresh(); /* Print it on to the real screen */
  getch();   /* Wait for user input */
moveCursor(1);
  endwin();  /* End curses mode     */

  return 0;
}


int moveCursor(int cMoves) {
	while(cMoves) {
		switch(getch()) {
			case 'a':
				if(cursor.x >3) cursor.x -= 2;
				break;
			case 'd':
				if(cursor.x < 20) cursor.x += 2;
				break;
			case 'w':
			if(cursor.y > 2) cursor.y -= 1;
				break;
			case 's':
				if(cursor.y < 11) cursor.y += 1;
				break;
		}
  	move(cursor.y,cursor.x);
	  refresh();
	}
  return 1;
}