#pragma once
#include <Maths/Vector.hpp>
#include <Maths/ViewMatrix.h>
#include <SDK/Maths/CView.h>
#include <Globals/Offsets.h>
#include <Globals/Globals.h>
#include <Main/Driver.h>
#include <SDK/CBone.h>
#include <SDK/CGame.h>

class CEntities
{
public:
	CHAR		Names[128] = { 0 };
	INT			Team;
	INT			Health;
	INT			Armor;
	UINTPTR		BoneMatrix;

	UINT32		Ping;
	UINT32		IsShotsFired;
	UINT32		Flag;

	Vector3		Position;
	Vector3		View;
	Vector3		Velocity;

	bool		IsCrouched;
	bool		IsStanding;
	bool		IsInAir;
	bool		IsNoCliped;
	bool		IsScoped;
	bool		IsFiring;
	bool		Alive;
	bool		Dead;
	bool		IsAboutToDie;
	bool		IsDormant;

	FLOAT GetHeadHeight(Vector2 Entity2DScreenProjection, Vector2 Head2DScreenProjection)
	{
		return (Entity2DScreenProjection.y - Head2DScreenProjection.y) / 8;
	}

	ImColor	GetColorHealth()
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

	VOID READ(UINTPTR CCSPlayerPawn, UINTPTR CCSPlayerController)
	{
		if (CCSPlayerPawn != NULL)
		{
			this->Team = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_iTeamNum);
			this->Health = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_iHealth);
			this->Armor = Driver::RPM<INT>(CCSPlayerPawn + Offsets::m_ArmorValue);
			this->BoneMatrix = cBone.GetMatrix(CCSPlayerPawn);
			this->Position = Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vOldOrigin);
			this->View = cView.GetCurrentView(CCSPlayerPawn);
			this->Velocity = Driver::RPM<Vector3>(CCSPlayerPawn + Offsets::m_vecAbsVelocity);
			this->IsScoped = Driver::RPM<bool>(CCSPlayerPawn + Offsets::m_bIsScoped);
			this->IsShotsFired = Driver::RPM<UINT32>(CCSPlayerPawn + Offsets::m_iShotsFired);
			this->Flag = Driver::RPM<UINT32>(CCSPlayerPawn + Offsets::m_fFlags);
			this->IsDormant = Driver::RPM<bool>(CCSPlayerPawn + Offsets::m_bDormant);
		}

		if (CCSPlayerController != NULL)
		{
			this->Ping = Driver::RPM<UINT32>(CCSPlayerController + Offsets::m_iPing);
			UINTPTR NAME_PTR = Driver::RPM<UINTPTR>(CCSPlayerController + Offsets::m_sSanitizedPlayerName);
			if (NAME_PTR != NULL)
				Driver::RPM_Array<CHAR>(NAME_PTR, this->Names, sizeof(Names));
		}

		// Entities States and Misc's
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

		if (this->Health > 0) { this->Alive = true; this->Dead = false; }
		else { this->Alive = false; this->Dead = true; }

		if (this->Health <= 15) this->IsAboutToDie == true;
		else this->IsAboutToDie == false;
	}

}; 

// Player Entities Class (CEntities)
inline CEntities cEntities[64];