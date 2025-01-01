#include "sdkincs.h"

namespace Aimbot
{
	inline Vector3 SetHeadCoordinates(uintptr_t boneMatrix)
	{
		Vector3 entityPosition = Driver::RPM<Vector3>(boneMatrix + (CBone::Index::HEAD * 0x20));
		return entityPosition;
	}

	inline VOID Aimbot(UINTPTR Client)
	{
		if (cEntities->IsDead)
			return;

		if (cEntities->Team == cPlayer.Team)
			return;

		Vector3 PlayerView = cPlayer.Position + cPlayer.View;
		Vector3 EntityView = cEntities->Position + cEntities->View;

		Vector2 NewAngles2D = cAngle.CalculateAngles(PlayerView, SetHeadCoordinates(cEntities->BoneMatrix));
		Vector3 NewAngles3D = Vector3(NewAngles2D.y, NewAngles2D.x, 0.0f);

		cAngle.SetViewAngles(Client, NewAngles3D);
	}
}