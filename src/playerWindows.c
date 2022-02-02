#include "playerWindows.h"

void overwriteMainWindow(PlayerWindows *windows) {
	overwrite(windows->info, windows->main);
	overwrite(windows->name, windows->main);
	overwrite(windows->tracking, windows->main);
	overwrite(windows->primary, windows->main);
}

void eraseAllWindows(PlayerWindows *windows) {
	werase(windows->main);
	werase(windows->primary);
	werase(windows->tracking);
	werase(windows->name);
	werase(windows->info);
}