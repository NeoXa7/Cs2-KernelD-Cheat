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