#include "CAngle.h"
#define M_PI 3.14159265358979323846

Vector2 CAngle::CalculateAngles(Vector3 from, Vector3 to)
{
	Float yaw, pitch;
	Float deltaX = to.x - from.x;
	Float deltaY = to.y - from.y;
	yaw = (Float)(std::atan2(deltaY, deltaX) * 180 / M_PI);

	Float deltaZ = to.z - from.z;
	double distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));

	pitch = -(Float)(std::atan2(deltaZ, distance) * 180 / M_PI);

	return Vector2(yaw, pitch);
}
