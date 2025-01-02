#pragma once
#include <WinUser.h>
#include <Maths/Vector.hpp>

namespace Mouse
{
	namespace Move
	{
		VOID OnAxisY(int dx, int dy);
		VOID OnAxisX(int dx, int dy);
		VOID ToClosest2DVector(Vector2 position);
		VOID To(int deltaX, int deltaY);
	}

	namespace Click
	{
		VOID LMB();
		VOID RMB();
		VOID MMB();
		VOID X1MB();
		VOID X2MB();
	}
}

namespace Keyboard
{
	inline static VOID SendKeyPress(char key)
	{
		// Implement your key press simulation logic (e.g., using SendInput on Windows)
		INPUT input = { 0 };
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;  // Virtual key code for the key you want to simulate
		input.ki.dwFlags = 0; // Key down event
		SendInput(1, &input, sizeof(INPUT));

		// Simulate key release
		input.ki.dwFlags = KEYEVENTF_KEYUP;  // Key up event
		SendInput(1, &input, sizeof(INPUT));
	}
}

inline VOID Mouse::Move::To(int deltaX, int deltaY)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE; // Relative mouse movement
	input.mi.dx = deltaX;
	input.mi.dy = deltaY;

	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Move::OnAxisY(int dx, int dy)
{
	INPUT input = { 0 };

	// Move mouse vertically
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	input.mi.dwExtraInfo = 0;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Move::OnAxisX(int dx, int dy)
{
	INPUT input = { 0 };

	// Move mouse horizontally
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	input.mi.dwExtraInfo = 0;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Move::ToClosest2DVector(Vector2 position)
{
	if (position.x == 0.0 && position.y == 0.0)
		return;

	Vector2 Center_Of_Screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 };

	auto new_x = position.x - Center_Of_Screen.x;
	auto new_y = position.y - Center_Of_Screen.y;

	mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
}

inline VOID Mouse::Click::LMB()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Click::RMB()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Click::MMB()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Click::X1MB()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_XDOWN;
	input.mi.mouseData = XBUTTON1;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_XUP;
	input.mi.mouseData = XBUTTON1;
	SendInput(1, &input, sizeof(INPUT));
}

inline VOID Mouse::Click::X2MB()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_XDOWN;
	input.mi.mouseData = XBUTTON2;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_XUP;
	input.mi.mouseData = XBUTTON2;
	SendInput(1, &input, sizeof(INPUT));
}