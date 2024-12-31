#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <Maths/W2S.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <SDK/CGameConstants.h>
#include <SDK/CPlayerComponents.h>
#include <SDK/CEntityComponents.h>
#include <Main/Driver.h>

class Game
{
public:
	CHAR			MapName[128] = { 0 };

	UINTPTR			Planted_C4;
	UINTPTR			Weapon_C4;
	UINTPTR			EntityList;
	UINTPTR			Rules;
	UINTPTR			GlobalVars;
	UINTPTR			CameraServices;

	FLOAT			FlashDuration;
	INT				EntityIndex;
	Vector3			ViewAngles;
	view_matrix_t	ViewMatrix;

	bool			IsBombPlanted;
	bool			IsBombDropped;
	bool			IsBombBeingDefused;
	bool			IsWarmupPeriod;
	bool			IsTerroristTimeOutActive;
	bool			IsCtTimeOutActive;

	VOID READ(uintptr_t Client, uintptr_t MatchMakingDll)
	{
		UINTPTR MAP_NAME_PTR = Driver::RPM<UINTPTR>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
		Driver::RPM_Array<CHAR>(MAP_NAME_PTR, this->MapName, sizeof(MapName));

		// Pointer Derefrencing
		{
			this->Planted_C4 = Driver::RPM<UINTPTR>
				(this->Planted_C4 = Driver::RPM<UINTPTR>(Client + Offsets::dwPlantedC4));

			this->Weapon_C4 = Driver::RPM<UINTPTR>
				(this->Weapon_C4 = Driver::RPM<UINTPTR>(Client + Offsets::dwWeaponC4));
		}

		this->EntityList = Driver::RPM<UINTPTR>(Client + Offsets::dwEntityList);
		this->Rules = Driver::RPM<UINTPTR>(Client + Offsets::dwGameRules);
		this->GlobalVars = Driver::RPM<UINTPTR>(Client + Offsets::dwGlobalVars);
		this->CameraServices = Driver::RPM<UINTPTR>(localplayer.Pawn + Offsets::m_pCameraServices);

		this->FlashDuration = Driver::RPM<FLOAT>(localplayer.Pawn + Offsets::m_flFlashBangTime);
		this->EntityIndex = Driver::RPM<INT>(localplayer.Pawn + Offsets::m_iIDEntIndex);
		this->ViewAngles = Driver::RPM<Vector3>(Client + Offsets::dwViewAngles);
		this->ViewMatrix = Driver::RPM<view_matrix_t>(Client + Offsets::dwViewMatrix);

		this->IsBombPlanted = Driver::RPM<bool>(this->Rules + Offsets::m_bBombPlanted);
		this->IsBombDropped = Driver::RPM<bool>(this->Rules + Offsets::m_bBombDropped);
		this->IsBombBeingDefused = Driver::RPM<bool>(this->Planted_C4 + Offsets::m_bBeingDefused);
		this->IsWarmupPeriod = Driver::RPM<bool>(this->Rules + Offsets::m_bWarmupPeriod);
		this->IsTerroristTimeOutActive = Driver::RPM<bool>(Rules + Offsets::m_bTerroristTimeOutActive);
		this->IsCtTimeOutActive = Driver::RPM<bool>(Rules + Offsets::m_bCTTimeOutActive);

		return VOID();
	}

}; inline Game game;