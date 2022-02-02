#include "setLocaleUTF8.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#endif
#include <locale.h>

void setLocaleUTF8() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	SetConsoleOutputCP(CP_UTF8);

#endif
	setlocale(LC_ALL, "en_US.UTF-8");
}