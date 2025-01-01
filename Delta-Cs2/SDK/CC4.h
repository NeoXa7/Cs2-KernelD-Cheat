#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <SDK/Maths/CView.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <SDK/CGameConstants.h>
#include <SDK/CPlayer.h>
#include <SDK/CGame.h>
#include <Main/Driver.h>

class CC4
{
public:
	float bombTimer = 40.0f;

	Vector3 GetPlantedC4Position()
	{
		UINTPTR pc4Node = Driver::RPM<UINTPTR>(cGame.Planted_C4 + Offsets::m_pGameSceneNode);
		return Driver::RPM<Vector3>(pc4Node + Offsets::m_vecAbsOrigin);
	}

	Vector3 GetDroppedC4Position()
	{
		UINTPTR dc4Node = Driver::RPM<UINTPTR>(cGame.Weapon_C4 + Offsets::m_pGameSceneNode);
		return Driver::RPM<Vector3>(dc4Node + Offsets::m_vecAbsOrigin);
	}

	INT	GetBombSite()
	{
		return Driver::RPM<INT>(cGame.Planted_C4 + Offsets::m_nBombSite);
	}

	FLOAT GetPC4ToLocalDistance()
	{
		return (GetPlantedC4Position() - cPlayer.Position).Magnitude(); // In Units;
	}

	FLOAT GetDC4ToLocalDistance()
	{
		return (GetDroppedC4Position() - cPlayer.Position).Magnitude(); // In Units;
	}

	VOID UpdateBombTimer() {
		if (cGame.IsBombPlanted) {
			// Countdown only if the bomb is planted
			if (bombTimer > 0.0f) {
				bombTimer -= 1.0f / 60.0f;  // Decrease timer by 1/60 of a second per frame
			}
			else {
				bombTimer = 0.0f;  // Timer cannot go below 0
			}
		}
		else {
			// Reset the timer if the bomb is not planted
			bombTimer = 40.0f;
		}
	}

}; inline CC4 cC4;
