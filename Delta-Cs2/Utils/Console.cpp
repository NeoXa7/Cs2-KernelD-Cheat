#include <Utils/Console.hpp>

VOID Console::SetConsoleTextColor(WORD color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

VOID Console::CreateConsoleWindow(CONST WCHAR* title, INT Width, INT Height)
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
	//freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr

	SetConsoleTitle(title);

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL)
	{
		MoveWindow(consoleWindow, 100, 100, Width, Height, TRUE);
	}
}

VOID Console::DestroyConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow(); // Get the console window handle
	if (consoleWindow != NULL)
	{
		FreeConsole(); // Detach the console from the current process
		PostMessage(consoleWindow, WM_CLOSE, 0, 0); // Send a close message to the console window
	}
}

VOID Console::CreateLogNotification(CONST std::string& LogsName, CONST std::string& logFileName)
{
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	std::cout
		<< " [INFO] "
		<< LogsName
		<< " Logs have been created at: "
		<< logFileName
		<< " ("
		<< std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
		<< ")"
		<< '\n';
	std::cout << '\n';
}
