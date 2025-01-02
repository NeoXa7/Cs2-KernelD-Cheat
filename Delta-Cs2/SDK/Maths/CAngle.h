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
	Vector3 GetCurrentViewAngles(UINTPTR Client)
	{
		Vector3 currentAngles = Driver::RPM<Vector3>(Client + Offsets::dwViewAngles);
		return currentAngles;
	}

	// Sets Current View Angle to New 3D Vector
	Vector3 SetViewAngles(UINTPTR Client, Vector3 AngleToSet)
	{
		return Driver::WPM<Vector3>(Client + Offsets::dwViewAngles, AngleToSet);
	}

	Vector3 LerpAngles(const Vector3& start, const Vector3& end, float t)
	{
		return Vector3(
			start.x + (end.x - start.x) * t,
			start.y + (end.y - start.y) * t,
			start.z + (end.z - start.z) * t
		);
	}
}; 

// Game View Angles Functions (CAngles Class)
inline CAngle cAngle;