#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */

  printw(
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
			"--------------------------------------------\n");

	refresh();			/* Print it on to the real screen */
  getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
