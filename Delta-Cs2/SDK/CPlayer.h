#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <SDK/Maths/CView.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <Main/Driver.h>
#include <SDK/CGameConstants.h>

class CPlayer
{
public:
	UINTPTR		Pawn;
	UINTPTR		Controller;

	CHAR		Name[128] = { 0 };
	INT			Team;
	INT			Health;
	INT			Armor;

	UINT32		Ping;
	UINT32		IsShotsFired;
	UINT32		Flag;

	FLOAT		Sensitivity;
	FLOAT		AimPunchAngle;

	Vector3		ViewAngles;
	Vector3		Position;
	Vector3		LastPosition;
	Vector3		View;
	Vector3		Velocity;

	bool		IsCrouched;
	bool		IsStanding;
	bool		IsInAir;
	bool		IsNoCliped;
	bool		IsScoped;
	bool		IsFiring;
	bool		IsAlive;
	bool		IsDead;
	bool		IsAboutToDie;
	bool        IsIdle;

	inline VOID	READ(uintptr_t Client)
	{
		UINTPTR SENSITIVITY_PTR = Driver::RPM<UINTPTR>(Client + Offsets::dwSensitivity);
		if (SENSITIVITY_PTR) {
			this->Sensitivity = Driver::RPM<FLOAT>(SENSITIVITY_PTR + Offsets::dwSensitivity_sensitivity);
		}

		this->Pawn = Driver::RPM<UINTPTR>(CS2::ClientDll + Offsets::dwLocalPlayerPawn);
		if (this->Pawn != NULL)
		{
			this->Team = Driver::RPM<INT>(this->Pawn + Offsets::m_iTeamNum);
			this->Health = Driver::RPM<INT>(this->Pawn + Offsets::m_iHealth);
			this->Armor = Driver::RPM<INT>(this->Pawn + Offsets::m_ArmorValue);
			this->AimPunchAngle = Driver::RPM<FLOAT>(this->Pawn + Offsets::m_aimPunchAngle);
			this->ViewAngles = Driver::RPM<Vector3>(this->Pawn + Offsets::dwViewAngles);
			this->Position = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vOldOrigin);
			this->View = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vecViewOffset);
			this->Velocity = Driver::RPM<Vector3>(this->Pawn + Offsets::m_vecAbsVelocity);
			this->IsScoped = Driver::RPM<bool>(this->Pawn + Offsets::m_bIsScoped);
			this->IsShotsFired = Driver::RPM<UINT32>(this->Pawn + Offsets::m_iShotsFired);
			this->Flag = Driver::RPM<UINT32>(this->Pawn + Offsets::m_fFlags);
		}

		this->Controller = Driver::RPM<UINTPTR>(Client + Offsets::dwLocalPlayerController);
		if (this->Controller != NULL)
		{
			UINTPTR NAME_PTR = Driver::RPM<UINTPTR>(this->Controller + Offsets::m_sSanitizedPlayerName);
			if (NAME_PTR != NULL)
			{
				Driver::RPM_Array<CHAR>(NAME_PTR, this->Name, sizeof(this->Name));
			}

			this->Ping = Driver::RPM<UINT32>(this->Controller + Offsets::m_iPing);
		}

		// Player States and Misc's
		if (this->Flag == CROUCHING) this->IsCrouched = true;
		else this->IsCrouched = false;

		if (this->Flag == STANDING) this->IsStanding = true;
		else this->IsStanding = false;

		if (this->Flag == INAIR)this->IsInAir = true;
		else this->IsInAir = false;

		if (this->Flag == ISNOCLIP) this->IsNoCliped = true;
		else this->IsNoCliped = false;

		if (this->IsShotsFired > 0) this->IsFiring = true;
		else this->IsFiring = false;

		if (this->Health > 0) { this->IsAlive = true; this->IsDead = false; }
		else { this->IsAlive = false; this->IsDead = true; }

		if (this->Health <= 15) this->IsAboutToDie == true;
		else this->IsAboutToDie == false;
	}

}; 

// Local Player Class (CPlayer)
inline CPlayer cPlayer;
