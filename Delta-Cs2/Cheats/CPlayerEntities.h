#pragma once
#include "sdkincs.h"

namespace CPlayerEntities
{
	// Locates all the entities in the game and renders ESP elements to reveal their locations and positions.
	extern VOID ExtraSensoryPreception(); // Defined in Esp.cpp inside Definations folder (is too long function). 

	// Identifies all the targets in the game and automatically adjusts the aim to align with their positions.
	inline VOID Aimbot()
	{

	}

	// Detects when a target is in the crosshair and automatically shoots. 
	inline VOID Triggerbot()
	{
		if (cGame.EntityIndex > 0)
		{
			uintptr_t entityListEntry = Driver::RPM<uintptr_t>(cGame.EntityList + 0x8 * (cGame.EntityIndex >> 9) + 0x10);
			uintptr_t entity = Driver::RPM<uintptr_t>(entityListEntry + 120 * (cGame.EntityIndex & 0x1FF));

			int entityTeam = Driver::RPM<int>(entity + Offsets::m_iTeamNum);
			int entityHealth = Driver::RPM<int>(entity + Offsets::m_iHealth);

			if (Data::TriggerBot::m_bEnableTeamCheck == TRUE)
			{
				if (entityTeam != cPlayer.Team && entityHealth > 0)
				{
					Mouse::Click::LMB();
					Sleep(100);
				}
			}
			else
			{
				if (entityHealth > 0)
				{
					Mouse::Click::LMB();
					Sleep(100);
				}
			}
		}
	}
}