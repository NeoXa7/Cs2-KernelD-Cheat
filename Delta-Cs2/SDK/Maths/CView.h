#pragma once
#include <Maths/Vector.hpp>
#include <Globals/Globals.h>
#include <Main/Driver.h>
#include <Globals/Offsets.h>


class CView
{
public:
	// Converts 3D Screen Coordiantes to 2D Screen Coordinates
	Bool Project3DWorldTo2D(const Vector3& worldPos, Vector2& screenPos, const view_matrix_t& viewMatrix);

	// Gets Current Vector View Offsets
	Vector3 GetCurrentView(UINTPTR CCSPlayerPawn)
	{
		return Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vecViewOffset);
	}

}; inline CView cView;