#include "events/endScreen/endScreen.h"
#include "input.h"
#include "playerWindows.h"
#include <curses.h>

const int WINNER_ROW = 11;
const int WINNER_COLUMN = 10;

StateType endScreen(Player *players, int currentPlayerIndex,
					PlayerWindows windows) {
	werase(windows.main);

	mvprintw(WINNER_ROW - 2, WINNER_COLUMN, "🎊 🎉🎊 🎉🎊 🎉🎊 🎉🎊 🎉🎊 🎉");
	mvprintw(WINNER_ROW, WINNER_COLUMN, "The winner is %s ",
			 players[currentPlayerIndex].name);
	mvprintw(WINNER_ROW + 2, WINNER_COLUMN, "🎊 🎉🎊 🎉🎊 🎉🎊 🎉🎊 🎉🎊 🎉");

	wrefresh(windows.main);

	getInput(-1);

	return QUIT;
}
