#pragma once
#include <Maths/Vector.hpp>
#include <Globals/Globals.h>
#include <Main/Driver.h>
#include <Globals/Offsets.h>

class CAngle
{
public:
	// Calculates Angle from one point to another
	Vector2 CalculateAngles(Vector3 from, Vector3 to);

	// Gets Current View Angles
	Vector2 GetCurrentViewAngles(UINTPTR Client)
	{
		Vector2 currentAngles = Driver::RPM<Vector2>(Client + Offsets::dwViewAngles);
		return currentAngles;
	}

	// Sets Current View Angle to New 3D Vector
	Vector3 SetViewAngles(UINTPTR Client, Vector3 AngleToSet)
	{
		return Driver::WPM<Vector3>(Client + Offsets::dwViewAngles, AngleToSet);
	}

}; 

// Game View Angles Functions (CAngles Class)
inline CAngle cAngle;