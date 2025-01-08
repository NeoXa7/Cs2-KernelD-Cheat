#pragma once
#include <Globals/Globals.h>
#include <Globals/Logo.h>
#include <Libs/imgui/imgui.h>
#include <Libs/imgui/imgui_internal.h>
#include "Resources.h"

// Groups for Each Features or Tabs
enum Groups
{
	PLAYER,
	BOMB,
	WORLD,
	AIMBOT,
	TRIGGERBOT,
	MEMORY,
	LOCALPLAYER,
	ENTITYLIST,
	MISCS,
	CONFIG,
	OFFSETS,
	OTHER_SETTINGS
};

class Menu
{
private:
	// Menu Styles
	VOID ApplyStyles();

	// Visuals Menu

	VOID CreatePlayerEspInterface();
	VOID CreateBombEspInterface();
	VOID CreateWorldEspInterface();

	// Rage Menu

	VOID CreateMemoryInterface();
	VOID CreateAimbotInterface();

	// Legit

	VOID CreateTriggerbotInterface();
	VOID CreateMiscInterface();

	// Local Player and Game info Interace Function

	VOID CreateLocalClientInfoInterface();
	VOID CreateEntitiesInterface();

	// Other Interfaces

	VOID CreateConfigManagerInterface();
	VOID CreateMenuSettingsInterface();
	VOID CreateOffsetsUpdaterInterface();


	INT tab_selection_count = 0; // Default Selected Visuals tab [ 0 ]

	INT visuals_group_count = 0; // Default Selected Player from groups {Player, Bomb, World} [0 1 2]
	INT legit_group_count = 3; // Default Selected Aimbot from groups {Aimbot, Triggerbot} [3 4]
	INT rage_group_count = 5; // Default Selected Memory from groups {Memory} [5]
	INT cplayerinfo_group_count = 6;  // Default Selected Player from groups {Player , Entities} [6 7]
	INT misc_group_count = 8;  // Default Selected MISCs from groups {Miscs} [8]
	INT settings_group_count = 9; // Default Selected Config Manager from groups {Configs, Offsets, Menu} [9 10 11]

public:
	// Main Renderer Function for the Cheat Menu or ImGui Menu
	VOID Render();
}; inline Menu menu;

