#pragma once
#include <Globals/Globals.h>

#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define MAGENTA FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GRAY FOREGROUND_INTENSITY
#define DARK_RED FOREGROUND_RED
#define DARK_GREEN FOREGROUND_GREEN
#define DARK_BLUE FOREGROUND_BLUE
#define DARK_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define DARK_MAGENTA FOREGROUND_RED | FOREGROUND_BLUE
#define DARK_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE

class Console
{
public:
	VOID SetConsoleTextColor(WORD color);
	VOID CreateConsoleWindow(CONST WCHAR* title, INT Width = 1000, INT Height = 600);
	VOID DestroyConsoleWindow();
	VOID CreateLogNotification(CONST std::string& LogsName, CONST std::string& logFileName);
}; inline Console console;