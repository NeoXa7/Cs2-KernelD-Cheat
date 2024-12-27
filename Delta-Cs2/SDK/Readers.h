#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <Maths/W2S.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <Driver.h>
#include "Bone.h"

// local player data
class LocalPlayer
{
public:
	Pointer		Pawn;
	Pointer		Controller;

	CHAR		Name[128] = { 0 };
	INT			Team;
	INT			Health;
	INT			Armor;

	UINT32		Ping;
	UINT32		IsFiring;
	UINT32		Flag;

	FLOAT		Sensitivity;
	FLOAT		AimPunchAngle;

	Vector3		ViewAngles;
	Vector3		Position;
	Vector3		VecViewOffset;
	Vector3		Velocity;

	bool		IsCrouched; // null
	bool		IsScoped;

	inline VOID	READ(uintptr_t Client)
	{
		Pointer SENSITIVITY_PTR = Driver::RPM<Pointer>(Client + Offsets::dwSensitivity);
		if (SENSITIVITY_PTR) {
			this->Sensitivity = Driver::RPM<FLOAT>(SENSITIVITY_PTR + Offsets::dwSensitivity_sensitivity);
		}

		this->Pawn = Driver::RPM<Pointer>(CS2::ClientDll + Offsets::dwLocalPlayerPawn);
		if (this->Pawn != NULL)
		{
			this->Team = Driver::RPM<INT>(this->Pawn + Offsets::m_iTeamNum);
			this->Health = Driver::RPM<INT>(this->Pawn + Offsets::m_iHealth);
			this->Armor = Driver::RPM<INT>(this->Pawn + Offsets::m_ArmorValue);
			this->AimPunchAngle = Driver::RPM<FLOAT>(this->Pawn + Offsets::m_aimPunchAngle);
			this->ViewAngles = Driver::RPM<Vector3>(this->Pawn + Offsets::dwViewAngles);
			this->Position = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vOldOrigin);
			this->VecViewOffset = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vecViewOffset);
			this->Velocity = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vecAbsVelocity);
			this->IsScoped = Driver::RPM<bool>(this->Pawn + Offsets::m_bIsScoped);
			this->IsFiring = Driver::RPM<UINT32>(this->Pawn + Offsets::m_iShotsFired);
			this->Flag = Driver::RPM<UINT32>(this->Pawn + Offsets::m_fFlags);
		}

		this->Controller = Driver::RPM<Pointer>(Client + Offsets::dwLocalPlayerController);
		if (this->Controller != NULL)
		{
			Pointer NAME_PTR = Driver::RPM<Pointer>(this->Controller + Offsets::m_sSanitizedPlayerName);
			if (!NAME_PTR == NULL)
			{
				Driver::RPM_Array<CHAR>(NAME_PTR, this->Name, sizeof(this->Name));
			}

			this->Ping = Driver::RPM<UINT32>(this->Controller + Offsets::m_iPing);
		}

		this->IsCrouched = NULL;
	}

}; inline LocalPlayer localplayer;

// game entities data
class Entities
{
public:
	CHAR		Names[128] = { 0 };
	INT			Team;
	INT			Health;
	INT			Armor;
	Pointer		BoneMatrix;

	UINT32		Ping;
	UINT32		IsFiring;

	Vector3		Position;
	Vector3		VecViewOffset;
	Vector3		Velocity;

	bool		IsScoped;
	bool		IsDormant;
	
	FLOAT		GetHeadHeight(Vector2 Entity2DScreenProjection, Vector2 Head2DScreenProjection)
	{
		return (Entity2DScreenProjection.y - Head2DScreenProjection.y) / 8;
	}

	ImColor		GetColorHealth()
	{
		if (this->Health >= 100)
		{
			return ImColor(0, 255, 0, 255); // Green for full health
		}
		else if (this->Health >= 60)
		{
			return ImColor(255, 255, 0, 255); // Yellow for medium health
		}
		else if (this->Health >= 30)
		{
			return ImColor(255, 165, 0, 255); // Orange for low health
		}
		else
		{
			return ImColor(255, 0, 0, 255); // Red for critical health
		}
	}

	VOID		READ(Pointer CCSPlayerPawn, Pointer CCSPlayerController)
	{
		if (CCSPlayerPawn != NULL)
		{
			this->Team = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_iTeamNum);
			this->Health = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_iHealth);
			this->Armor = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_ArmorValue);
			this->BoneMatrix = bone.GetMatrix(CCSPlayerPawn);
			this->Position = Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vOldOrigin);
			this->VecViewOffset = Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vecViewOffset);
			this->Velocity = Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vecAbsVelocity);
			this->IsScoped = Driver::RPM<bool>(CCSPlayerPawn + Offsets::m_bIsScoped);
			this->IsFiring = Driver::RPM<UINT32>(CCSPlayerPawn + Offsets::m_iShotsFired);
			this->IsDormant = Driver::RPM<bool>(CCSPlayerPawn + Offsets::m_bDormant);
		}

		if (CCSPlayerController != NULL)
		{
			this->Ping = Driver::RPM<UINT32>(CCSPlayerController + Offsets::m_iPing);
			Pointer NAME_PTR = Driver::RPM<Pointer>(CCSPlayerController + Offsets::m_sSanitizedPlayerName);
			if (!NAME_PTR == NULL)
				Driver::RPM_Array<CHAR>(NAME_PTR, this->Names, sizeof(Names));
		}

		return VOID();
	}

}; inline Entities entities[64];

// game variables data
class Game
{
public:
	CHAR			MapName[128] = { 0 };

	Pointer			Planted_C4;
	Pointer			Weapon_C4;
	Pointer			EntityList;
	Pointer			Rules;
	Pointer			GlobalVars;
	Pointer			CameraServices;
	
	FLOAT			FlashDuration;
	FLOAT			EntitiesToLocalDist;
	INT				EntityIndex;
	Vector3			ViewAngles;
	view_matrix_t	ViewMatrix;

	bool			BombPlanted;
	bool			BombDropped;
	bool			IsBombBeingDefused;
	bool			IsWarmupPeriod;
	bool			IsTerroristTimeOutActive;
	bool			IsCtTimeOutActive;

	VOID READ(uintptr_t Client, uintptr_t MatchMakingDll)
	{
		Pointer MAP_NAME_PTR = Driver::RPM<Pointer>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
		Driver::RPM_Array<CHAR>(MAP_NAME_PTR, this->MapName, sizeof(MapName));

		// Pointer Derefrencing
		{
			this->Planted_C4 = Driver::RPM<Pointer>
				(this->Planted_C4 = Driver::RPM<Pointer>(Client + Offsets::dwPlantedC4));

			this->Weapon_C4 = Driver::RPM<Pointer>
				(this->Weapon_C4 = Driver::RPM<Pointer>(Client + Offsets::dwWeaponC4));
		}

		this->EntityList = Driver::RPM<Pointer>(Client + Offsets::dwEntityList);
		this->Rules = Driver::RPM<Pointer>(Client + Offsets::dwGameRules);
		this->GlobalVars = Driver::RPM<Pointer>(Client + Offsets::dwGlobalVars);
		this->CameraServices = Driver::RPM<Pointer>(localplayer.Pawn + Offsets::m_pCameraServices);

		this->FlashDuration = Driver::RPM<FLOAT>(localplayer.Pawn + Offsets::m_flFlashBangTime);
		this->EntitiesToLocalDist = (entities->Position - localplayer.Position).Magnitude(); // In Units;
		this->EntityIndex = Driver::RPM<INT>(localplayer.Pawn + Offsets::m_iIDEntIndex);
		this->ViewAngles = Driver::RPM<Vector3>(Client + Offsets::dwViewAngles);
		this->ViewMatrix = Driver::RPM<view_matrix_t>(Client + Offsets::dwViewMatrix);

		this->BombPlanted = Driver::RPM<bool>(this->Rules + Offsets::m_bBombPlanted);
		this->BombDropped = Driver::RPM<bool>(this->Rules + Offsets::m_bBombDropped);
		this->IsBombBeingDefused = Driver::RPM<bool>(this->Planted_C4 + Offsets::m_bBeingDefused);
		this->IsWarmupPeriod = Driver::RPM<bool>(this->Rules + Offsets::m_bWarmupPeriod);
		this->IsTerroristTimeOutActive = Driver::RPM<bool>(Rules + Offsets::m_bTerroristTimeOutActive);
		this->IsCtTimeOutActive = Driver::RPM<bool>(Rules + Offsets::m_bCTTimeOutActive);

		return VOID();
	}

}; inline Game game;


// bomb/c4 data
class C4
{
public:
	Vector3 GetPlantedC4Position()
	{
		Pointer pc4Node = Driver::RPM<Pointer>(game.Planted_C4 + Offsets::m_pGameSceneNode);
		return Driver::RPM<Vector3>(pc4Node + Offsets::m_vecAbsOrigin);
	}

	Vector3 GetDroppedC4Position()
	{
		Pointer dc4Node = Driver::RPM<Pointer>(game.Weapon_C4 + Offsets::m_pGameSceneNode);
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

// world data
class World
{
public:
	// Function to retrieve item names
	std::string GetWeaponType(const std::string& itemIdentifier, const std::unordered_map<std::string, std::string> weapons_type_map)
	{
		auto it = weapons_type_map.find(itemIdentifier);
		if (it != weapons_type_map.end())
			return it->second;
		return "<unknown>";
	}

	std::string GetProjectileType(const std::string& itemIdentifier, const std::unordered_map<std::string, std::string> projectiles_type_map)
	{
		auto it = projectiles_type_map.find(itemIdentifier);
		if (it != projectiles_type_map.end())
			return it->second;
		return "<unknown>";
	}

	std::string GetEntityType(const std::string& itemIdentifier, const std::unordered_map<std::string, std::string> entity_type_map)
	{
		auto it = entity_type_map.find(itemIdentifier);
		if (it != entity_type_map.end())
			return it->second;
		return "<unknown>";
	}

}; inline World world;