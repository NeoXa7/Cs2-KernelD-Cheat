#pragma once
#include <WinUser.h>
#include <Maths/Vector.hpp>

namespace Mouse
{
	namespace Move
	{
		inline VOID OnAxisY(int dx, int dy)
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

		inline VOID OnAxisX(int dx, int dy)
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

		inline VOID ToClosest2DVector(Vector2 position)
		{
			if (position.x == 0.0 && position.y == 0.0)
				return;

			Vector2 Center_Of_Screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 };

			auto new_x = position.x - Center_Of_Screen.x;
			auto new_y = position.y - Center_Of_Screen.y;

			mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
		}
	}

	namespace Click
	{
		inline VOID LMB()
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

		inline VOID RMB()
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

		inline VOID MMB()
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

		inline VOID X1MB()
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

		inline VOID X2MB()
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
	}
}