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
	MISC,
	MEMORY,
	LOCALPLAYER,
	ENTITYLIST,
	CONFIG,
	OFFSETS,
	SETTINGS
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
	VOID CreateSettingsInterface();


	INT tab_selection_count = 0;

	INT visuals_group_count = 0;
	INT legit_group_count = 3;
	INT rage_group_count = 6;
	INT cplayerinfo_group_count = 7;
	INT misc_group_count = 9;
	INT settings_group_count = 11;

public:
	// Main Renderer Function for the Cheat Menu or ImGui Menu
	VOID Render();
}; inline Menu menu;

