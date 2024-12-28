#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <Maths/W2S.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <SDK/CGameConstants.h>
#include <SDK/CPlayerComponents.h>
#include <SDK/CGameComponents.h>
#include <Main/Driver.h>

class C4
{
public:
	Vector3 GetPlantedC4Position()
	{
		UINTPTR pc4Node = Driver::RPM<UINTPTR>(game.Planted_C4 + Offsets::m_pGameSceneNode);
		return Driver::RPM<Vector3>(pc4Node + Offsets::m_vecAbsOrigin);
	}

	Vector3 GetDroppedC4Position()
	{
		UINTPTR dc4Node = Driver::RPM<UINTPTR>(game.Weapon_C4 + Offsets::m_pGameSceneNode);
		return Driver::RPM<Vector3>(dc4Node + Offsets::m_vecAbsOrigin);
	}

	INT	GetBombSite()
	{
		return Driver::RPM<INT>(game.Planted_C4 + Offsets::m_nBombSite);
	}

	FLOAT GetPC4ToLocalDistance()
	{
		return (GetPlantedC4Position() - localplayer.Position).Magnitude(); // In Units;
	}

	FLOAT GetDC4ToLocalDistance()
	{
		return (GetDroppedC4Position() - localplayer.Position).Magnitude(); // In Units;
	}

}; inline C4 c4;
