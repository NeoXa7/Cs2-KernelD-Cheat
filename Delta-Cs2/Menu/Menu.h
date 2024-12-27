#pragma once
#include <Globals/Globals.h>
#include <Globals/Logo.h>
#include <Libs/imgui/imgui.h>
#include <Libs/imgui/imgui_internal.h>
#include "Resources.hpp"

enum Groups
{
	PLAYER,
	BOMB,
	WORLD,
	AIMBOT,
	TRIGGERBOT,
	MISC,
	MEMORY,
	SETTINGS
};

class Menu
{
private:
	VOID ApplyStyles();

	// Visuals Menu
	VOID CreatePlayerEspInterfaces();
	VOID CreateBombEspInterfaces();
	VOID CreateWorldEspInterfaces();

	// Memory Cheats
	VOID CreateMemoryInterfaces();

	INT tab_selection_count = 0;

	INT visuals_group_count = 0;
	INT legit_group_count = 3;
	INT rage_group_count = 6;
	INT settings_group_count = 7;

public:
	VOID Render();
}; inline Menu menu;

