#pragma once
#include <Globals/Globals.h>
#include <Cheats/Data.h>
#include <Utils/Draw.h>
#include <Utils/Automation.h>
#include <SDK/CBoneComponents.h>
#include <SDK/CC4Components.h>
#include <SDK/CPlayerComponents.h>
#include <SDK/CEntityComponents.h>
#include <SDK/CGameComponents.h>
#include <SDK/CGameConstants.h>
#include <SDK/CGameObjectTypes.h>

// Main Class for Cheats
class Cheats
{
public:
	// Loop for Player Entities (Iterates Over 0 to 64 Entities)
	VOID BeginPlayerEntityLoop(uintptr_t ClientDll, uintptr_t MatchmakingDll)
	{
		game.READ(ClientDll, MatchmakingDll);
		localplayer.READ(ClientDll);

		for (int i = 0; i < 64; i++)
		{
			UINTPTR ListEntry = Driver::RPM<UINTPTR>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!ListEntry)
				continue;

			UINTPTR CCSPlayerController = Driver::RPM<UINTPTR>(ListEntry + 120 * (i & 0x1FF));
			if (!CCSPlayerController)
				continue;

			UINTPTR PawnHandle = Driver::RPM<UINTPTR>(CCSPlayerController + Offsets::m_hPlayerPawn);
			if (!PawnHandle)
				continue;

			UINTPTR ListEntry2 = Driver::RPM<UINTPTR>(game.EntityList + 0x8 * ((PawnHandle & 0x7FFF) >> 9) + 16);
			if (!ListEntry2)
				continue;

			UINTPTR CCSPlayerPawn = Driver::RPM<UINTPTR>(ListEntry2 + 120 * (PawnHandle & 0x1FF));
			if (!CCSPlayerPawn)
				continue;

			entities->READ(CCSPlayerPawn, CCSPlayerController);
			game.READ(ClientDll, MatchmakingDll);

			if (CCSPlayerPawn == localplayer.Pawn) // Ensures that the cheat logic for entities doesn't apply to ourselves or the local player.
				continue;

			if (Flags::VisualCheats == ENABLED)
			{
				// Player Esp
				{
					if (Data::Esp::m_bPlayerEsp == TRUE)
					{
						if (Data::Esp::Player::m_bTeamCheck == TRUE)
						{
							if (entities->Team == localplayer.Team)
								continue;
						}

						this->DrawPlayerEntityEsp();

						// Bone Esp
						if (Data::Esp::Player::m_bEnableBones == TRUE)
						{
							if (Data::Esp::Player::m_bBonesOnDeadEntity == FALSE)
							{
								if (entities->Health <= 0)
									return;
							}

							Draw::Bones(
								entities->BoneMatrix, entities->Position, game.ViewMatrix, Data::Esp::Player::m_clBoneColor,
								Data::Esp::Player::m_clBoneHeadColor, Data::Esp::Player::m_flBonesThickness,
								Data::Esp::Player::m_bEnableBonesJoints, Data::Esp::Player::m_bBoneHeadFilled,
								Data::Esp::Player::m_flJointRadius, Data::Esp::Player::m_clBoneJointsColor
							);
						}

					}
				}

				// Bomb Esp
				{
					if (Data::Esp::m_bBombEsp == TRUE)
					{
						this->DrawBombEsp();
					}
				}

			} 

		}
	}

	// Seperate Loop for World Esp (Iterates Over 64 - 1024 Entities)
	VOID BeginWorldEntitiesLoop(uintptr_t ClientDll, uintptr_t MatchmakingDll)
	{
		if (Flags::VisualCheats == ENABLED && Data::Esp::m_bWorldEsp)
		{
			game.READ(ClientDll, MatchmakingDll);
			for (int i = 64; i < 1024; i++)
			{
				UINTPTR ItemEntityListEntry = Driver::RPM<UINTPTR>(game.EntityList + 8LL * ((i & 0x7FFF) >> 9) + 16);
				if (!ItemEntityListEntry)
					continue;

				UINTPTR ItemEntity = Driver::RPM<UINTPTR>(ItemEntityListEntry + 120LL * (i & 0x1FF)); // Item Entity
				if (!ItemEntity)
					continue;

				UINTPTR ItemEntityNode = Driver::RPM<UINTPTR>(ItemEntity + Offsets::m_pGameSceneNode); // Item Entity Node
				Vector3 ItemEntityOrigin = Driver::RPM<Vector3>(ItemEntityNode + Offsets::m_vecAbsOrigin); // Item Entity Origin


				Vector2 World2DScreenProjection;
				if (!Project3DWorldTo2D(ItemEntityOrigin, World2DScreenProjection, game.ViewMatrix))
					continue;

				UINTPTR ItemInfo = Driver::RPM<UINTPTR>(ItemEntity + 0x10);
				UINTPTR ItemType = Driver::RPM<UINTPTR>(ItemInfo + 0x20);


				if (ItemEntityOrigin.x)
				{
					char type[128]{};
					Driver::RPM_Array<char>(ItemType, type, sizeof(type));
					std::string Weapons = GetWeaponType(type, WeaponsType);
					std::string Projectiles = GetProjectileType(type, ProjectilesType);
					std::string Entity = GetEntityType(type, EntityType);

					if (Weapons != "<unknown>") // Dropped Weapon Esp
					{
						if (Data::Esp::World::m_bEnableDroppedWeaponEsp)
						{
							Draw::TextWithStroke(
								Weapons.c_str(),
								{ World2DScreenProjection.x, World2DScreenProjection.y },
								Data::Esp::World::m_clWeaponEspTextColor,
								Data::Esp::World::m_clWeaponEspTextStrokeColor
							);
						}
					}

					if (Projectiles != "<unknown>") // Projectiles Weapon Esp
					{
						if (Data::Esp::World::m_bEnableProjectilesEsp)
						{
							Draw::TextWithStroke(
								Projectiles.c_str(),
								{ World2DScreenProjection.x, World2DScreenProjection.y },
								Data::Esp::World::m_clProjectilesEspTextColor,
								Data::Esp::World::m_clProjectilesEspTextStrokeColor
							);
						}
					}


					if (Entity != "<unknown>") // Chicken Esp
					{
						if (Data::Esp::World::m_bEnableChickenEsp)
						{
							if (strstr(type, "chicken"))
							{
								Vector3 ChickenHeight = ItemEntityOrigin + Vector3{ 0.0f, 0.0f, 30.0f }; // Box Height 72 Units;

								Vector2 ChickenScreenPos;
								if (!Project3DWorldTo2D(ChickenHeight, ChickenScreenPos, game.ViewMatrix))
									return;

								float boxHeight = std::fabs(ChickenScreenPos.y - ItemEntityOrigin.y);
								float boxWidth = boxHeight * 0.9f;

								Vector2 topLeft(World2DScreenProjection.x - boxWidth / 2, ChickenScreenPos.y);
								Vector2 topRight(World2DScreenProjection.x + boxWidth / 2 + 12.0f, ChickenScreenPos.y);
								Vector2 bottomRight(World2DScreenProjection.x + boxWidth / 2, World2DScreenProjection.y);

								//Draw::Box(topLeft, bottomRight);

								Draw::TextWithStroke(
									"Chicken",
									{ World2DScreenProjection.x, World2DScreenProjection.y },
									Data::Esp::World::m_clChickenEspTextColor,
									Data::Esp::World::m_clChickenEspTextStrokeColor
								);
							}
						}
					}
				}

			}
		}	
	}
	
	// Non loop Cheats for LocalPlayer
	VOID BeginLocalCheats(uintptr_t Client)
	{
		if (Flags::MemoryCheats == ENABLED)
		{
			localplayer.READ(Client);

			// Antiflash
			if (Data::Memory::m_bEnableAntiflash == TRUE)
			{
				this->ChangeFlashAlpha();
			}

			// Fov Changer
			if (Data::Memory::m_bEnableFovChanger == TRUE)
			{
				this->ChangePlayerFov();
			}

			// Bunny Hop
			if (Data::Memory::m_bEnableBhop == TRUE)
			{
				this->DoBhop(Client);
			}
		}
		
		if (Flags::AimCheats == ENABLED)
		{
			localplayer.READ(Client);

			if (Data::Rcs::m_bRcs == TRUE)
			{
				this->DoStandaloneRcs();
			}
		}
	}

	// Runs on Seperate Thread for Better Performance
	VOID BeginTriggerBot();

private:

	VOID DrawPlayerEntityEsp();
	VOID DrawBombEsp();
	VOID ChangeFlashAlpha();
	VOID ChangePlayerFov();
	VOID DoBhop(uintptr_t Client);
	VOID DoStandaloneRcs();
	VOID JumpShot();

}; inline Cheats cheats;


// Defination for Drawing function of Player Entity Esp;
inline VOID Cheats::DrawPlayerEntityEsp()
{
	Vector3 HeadPosition = entities->Position + Vector3{ 0.0f,0.0f,72.0f };

	Vector2 EntitiesScreenPosition, EntitiesHeadScreenPos;

	Data::Esp::Player::m_clHealthBarColor = entities->GetColorHealth();

	if (Project3DWorldTo2D(entities->Position, EntitiesScreenPosition, game.ViewMatrix) &&  // Entities W2S Position;
		Project3DWorldTo2D(HeadPosition, EntitiesHeadScreenPos, game.ViewMatrix)) // Entities W2S Head Position;
	{
		float boxHeight = std::fabs(EntitiesHeadScreenPos.y - EntitiesScreenPosition.y);
		float boxWidth = boxHeight * 0.6f;

		Vector2 TopLeft(EntitiesScreenPosition.x - boxWidth / 2, EntitiesHeadScreenPos.y);
		Vector2 TopRight(EntitiesScreenPosition.x + boxWidth / 2 + 12.0f, EntitiesHeadScreenPos.y);
		Vector2 BottomRight(EntitiesScreenPosition.x + boxWidth / 2, EntitiesScreenPosition.y);

		if (entities->IsDead)
			return;

		if (Data::Esp::Player::m_bEnableBox == TRUE)
		{
			if (Data::Esp::Player::m_bBoxFilled == FALSE)
			{
				Draw::Box
				(
					TopLeft,
					BottomRight,
					Data::Esp::Player::m_clBoxUnfilledColor,
					Data::Esp::Player::m_flBoxUnfilledThickness
				);
			}
			else
			{
				//Data::Esp::Player::m_clBoxFilledColor = ImVec4(Data::Esp::Player::m_clBoxFilledColor, 3, 182, Data::Esp::Player::m_iBoxOpacity);
				Draw::FilledBox
				(
					TopLeft,
					BottomRight,
					Data::Esp::Player::m_clBoxFilledColor,
					Data::Esp::Player::m_flBoxUnfilledThickness,
					Data::Esp::Player::m_clBoxUnfilledColor
				);
			}
		}

		// Draw the Lines
		if (Data::Esp::Player::m_bEnableLines == TRUE)
		{
			switch (Data::Esp::Player::m_iCurrentLinePosIndex) {
			case 0: Data::Esp::Player::m_vecCurrentlinePos = ScreenTop; break; // Top
			case 1: Data::Esp::Player::m_vecCurrentlinePos = ScreenCenter; break; // Center
			case 2: Data::Esp::Player::m_vecCurrentlinePos = ScreenBottom; break; // Bottom
			default: Data::Esp::Player::m_vecCurrentlinePos = ScreenBottom; break; // Default
			}

			Vector2 line_pos_local = EntitiesScreenPosition;

			if (Data::Esp::Player::m_iCurrentLinePosIndex == 0)
			{
				line_pos_local.y = TopLeft.y;
			}

			if ((localplayer.Position - entities->Position).Magnitude() / GAME_METRIC_UNITS < Data::Esp::Player::m_flLineEndPointDisplayDistance)
			{
				Draw::Line
				(
					Data::Esp::Player::m_vecCurrentlinePos,
					line_pos_local,
					Data::Esp::Player::m_clLineColor,
					Data::Esp::Player::m_flLinesThickness,
					TRUE,
					2.5f,
					Data::Esp::Player::m_clLineColor
				);
			}
			else
			{
				Draw::Line
				(
					Data::Esp::Player::m_vecCurrentlinePos,
					line_pos_local,
					Data::Esp::Player::m_clLineColor,
					Data::Esp::Player::m_flLinesThickness
				);
			}
		}

		// Draw the Names
		if (Data::Esp::Player::m_bEnableNames == TRUE)
		{
			Vector2 namePos(EntitiesScreenPosition.x - 20.0f, EntitiesScreenPosition.y);
			float distanceFactor = 1.0f / (localplayer.Position - entities->Position).Magnitude() / GAME_METRIC_UNITS; // Scale the font inversely with distance
			float scaledFontSize = min(Data::Esp::Player::m_flNameTextSize * distanceFactor, 15.0f); // Minimum font size

			Draw::TextWithStroke(
				entities->Names,
				namePos,
				Data::Esp::Player::m_clNameColor,
				ImColor(10, 10, 10, 255),
				scaledFontSize
			);
		}

		// Draw the Healthbar
		if (Data::Esp::Player::m_bEnableHealthBar == TRUE)
		{
			Draw::HealthBar
			(
				TopLeft,
				BottomRight,
				entities->Health,
				Data::Esp::Player::m_clHealthBarColor,
				2.0f,
				4.0f
			);
		}

		// Draw the Health text
		if (Data::Esp::Player::m_bEnableHealthText == TRUE)
		{
			char healthText[16];
			snprintf(healthText, sizeof(healthText), "[%d]", entities->Health);

			// Calculate the position for the health text to be just above the health bar
			Vector2 healthBarTopLeft(TopLeft.x - 6.0f - 5.0f, BottomRight.y - (BottomRight.y - TopLeft.y));
			Vector2 healthTextPos(healthBarTopLeft.x - 35.0f, healthBarTopLeft.y);

			float distanceFactor = 1.0f / (localplayer.Position - entities->Position).Magnitude() / GAME_METRIC_UNITS; // Scale the font inversely with distance
			float scaledFontSize = max(Data::Esp::Player::m_flHealthTextSize * distanceFactor, 15.0f); // Minimum font size

			Draw::TextWithStroke
			(
				healthText,
				healthTextPos,
				Data::Esp::Player::m_clHealthBarColor,
				ImColor(10, 10, 10, 255),
				scaledFontSize
			);
		}

		// Draw the Armor bar
		if (Data::Esp::Player::m_bEnableArmorBar == TRUE)
		{
			if (entities->Team == 2)
			{
				Data::Esp::Player::m_clArmorBarColor = Data::Game::m_clTerroristColor;
			}
			else if (entities->Team == 3)
			{
				Data::Esp::Player::m_clArmorBarColor = Data::Game::m_clCounterTerroristColor;
			}

			Draw::HealthBar
			(
				TopRight,
				BottomRight,
				entities->Armor,
				Data::Esp::Player::m_clArmorBarColor,
				2.0f,
				8.0f
			);
		}

		// Bones function called inside main loop;

		// Draw the Distance Text
		if (Data::Esp::Player::m_bEnableDistance == TRUE)
		{
			char DistTextArray[128];
			snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", (localplayer.Position - entities->Position).Magnitude() / GAME_METRIC_UNITS);

			Draw::TextWithStroke(
				DistTextArray,
				TopRight,
				Data::Esp::Player::m_clDistanceTextColor,
				ImColor(10, 10, 10, 255),
				Data::Esp::Player::m_flDistanceTextSize
			);
		}

	}
}

// Defination for Drawing function of Bomb Entity Esp;
inline VOID Cheats::DrawBombEsp()
{
	Vector3 PlantedC4Pos3D = c4.GetPlantedC4Position();
	Vector3 DroppedC4Pos3D = c4.GetDroppedC4Position();
	float C4Width = 30.0f;
	float C4Height = 20.0f;

	switch (Data::Esp::Bomb::m_iCurrentLinePosIndex) {
	case 0: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenTop; break;
	case 1: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenCenter; break;
	case 2: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenBottom; break;
	default: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenBottom; break;
	}

	if (game.IsBombPlanted)
	{
		Vector2 Planted_C4_ScreenPos, PlantedC4Height;
		Vector3 PlantedC4HeightPos = PlantedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height };

		if (Project3DWorldTo2D(PlantedC4Pos3D, Planted_C4_ScreenPos, game.ViewMatrix) &&
			Project3DWorldTo2D(PlantedC4HeightPos, PlantedC4Height, game.ViewMatrix))
		{
			Data::Esp::Bomb::m_clPlantedC4BoxColor = ImVec4(Data::Esp::Bomb::m_clPlantedC4BoxColor.x, Data::Esp::Bomb::m_clPlantedC4BoxColor.y, Data::Esp::Bomb::m_clPlantedC4BoxColor.z, Data::Esp::Bomb::m_clPlantedC4BoxColor.w);
			float BoxHeight = std::fabs(PlantedC4Height.y - Planted_C4_ScreenPos.y);
			float boxWidth = BoxHeight * (C4Width / C4Height);

			Vector2 topLeftPBP(Planted_C4_ScreenPos.x - boxWidth / 2.0f, Planted_C4_ScreenPos.y - BoxHeight / 2.0f);
			Vector2 bottomRightPBP(Planted_C4_ScreenPos.x + boxWidth / 2.0f, Planted_C4_ScreenPos.y + BoxHeight / 2.0f);

			Draw::FilledBox(topLeftPBP, bottomRightPBP, Data::Esp::Bomb::m_clPlantedC4BoxColor, Data::Esp::Bomb::m_flBoxThickness);

			if (Data::Esp::Bomb::m_bEnableC4Lines == TRUE)
			{
				Draw::Line(Data::Esp::Bomb::m_vecCurrentlinePos, Planted_C4_ScreenPos, Data::Esp::Bomb::m_clC4LineColor, Data::Esp::Bomb::m_flLineThickness, true);
			}

			if (Data::Esp::Bomb::m_bEnableC4DistanceText == TRUE)
			{
				char DistTextArray[128];
				float PlantedC4_DistanceInMeters = c4.GetPC4ToLocalDistance() / GAME_METRIC_UNITS;
				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", PlantedC4_DistanceInMeters);

				Draw::TextWithStroke(DistTextArray, bottomRightPBP, Data::Esp::Bomb::m_clDistanceTextColor, ImColor(10, 10, 10, 255), 15.0f);
			}
		}
	}

	if (game.IsBombDropped)
	{
		Vector2 Dropped_C4_ScreenPos, Dropped_C4_Height;
		Vector3 DroppedC4HeightPos = DroppedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height };

		if (Project3DWorldTo2D(DroppedC4Pos3D, Dropped_C4_ScreenPos, game.ViewMatrix) &&
			Project3DWorldTo2D(DroppedC4HeightPos, Dropped_C4_Height, game.ViewMatrix))
		{
			Data::Esp::Bomb::m_clDroppedC4BoxColor = ImVec4(Data::Esp::Bomb::m_clDroppedC4BoxColor.x, Data::Esp::Bomb::m_clDroppedC4BoxColor.y, Data::Esp::Bomb::m_clDroppedC4BoxColor.z, Data::Esp::Bomb::m_clDroppedC4BoxColor.w);
			float BoxHeight = std::fabs(Dropped_C4_Height.y - Dropped_C4_ScreenPos.y);
			float boxWidth = BoxHeight * (C4Width / C4Height);

			Vector2 topLeftDBP(Dropped_C4_ScreenPos.x - boxWidth / 2.0f, Dropped_C4_ScreenPos.y - BoxHeight / 2.0f);
			Vector2 bottomRightDBP(Dropped_C4_ScreenPos.x + boxWidth / 2.0f, Dropped_C4_ScreenPos.y + BoxHeight / 2.0f);

			if (Data::Esp::Bomb::m_bEnableC4Box)
				Draw::FilledBox(topLeftDBP, bottomRightDBP, Data::Esp::Bomb::m_clDroppedC4BoxColor, Data::Esp::Bomb::m_flBoxThickness);

			if (Data::Esp::Bomb::m_bEnableC4Lines)
				Draw::Line(Data::Esp::Bomb::m_vecCurrentlinePos, Dropped_C4_ScreenPos, Data::Esp::Bomb::m_clC4LineColor, Data::Esp::Bomb::m_flLineThickness, true);


			if (Data::Esp::Bomb::m_bEnableC4DistanceText)
			{
				char DistTextArray[128];
				float DroppedC4_DistanceInMeters = c4.GetDC4ToLocalDistance() / GAME_METRIC_UNITS;
				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", DroppedC4_DistanceInMeters);

				Draw::TextWithStroke(DistTextArray, bottomRightDBP, Data::Esp::Bomb::m_clDistanceTextColor, ImColor(10, 10, 10, 255));
			}
		}
	}
}

// Defination for Changing Flash Alpha Value
inline VOID Cheats::ChangeFlashAlpha()
{
	Driver::WPM<float>(localplayer.Pawn + Offsets::m_flFlashMaxAlpha, Data::Memory::m_flFlashAlpha);
}

// Defination for Changing Player Field of View in Game
inline VOID Cheats::ChangePlayerFov()
{
	UINT16 m_iDesiredFov = (UINT16)Data::Fov::m_iDefaultFov;
	UINT16 currentFov = Driver::RPM<UINT64>(game.CameraServices + Offsets::m_iFOV);

	if (localplayer.IsScoped)
		return;

	if (currentFov != m_iDesiredFov)
	{
		Driver::WPM<UINT64>(game.CameraServices + Offsets::m_iFOV, m_iDesiredFov);
	}
}

// Defination for Automating Bunnyhop in Game
inline VOID Cheats::DoBhop(uintptr_t Client)
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		if (localplayer.Flag == STANDING || localplayer.Flag == CROUCHING)
		{
			Driver::WPM<int>(Client + Offsets::jump, PLUSJUMP);
			Sleep(10);
			Driver::WPM<int>(Client + Offsets::jump, MINUSJUMP);
		}
	}
}

// Defination for Automating Recoil Control
inline VOID Cheats::DoStandaloneRcs()
{
	float aimPunch_x = localplayer.AimPunchAngle;
	float aimPunch_y = Driver::RPM<float>(localplayer.Pawn + localplayer.AimPunchAngle + 0x4);

	if (localplayer.IsShotsFired > 1)
	{
		auto delta_x = (aimPunch_x - Data::Rcs::m_flOldPunchAngleX) * -1.0;
		auto delta_y = (aimPunch_y - Data::Rcs::m_flOldPunchAngleY) * -1.0;
		auto mouse_x = int((delta_y * 2.0 / localplayer.Sensitivity) / -0.022);
		auto mouse_y = int((delta_x * 2.0 / localplayer.Sensitivity) / 0.022);

		Mouse::Move::OnAxisX(mouse_x, mouse_y);
		Data::Rcs::m_flOldPunchAngleX = aimPunch_x;
		Data::Rcs::m_flOldPunchAngleY = aimPunch_y;
	}
	else
	{
		Data::Rcs::m_flOldPunchAngleX = aimPunch_x; // 0
		Data::Rcs::m_flOldPunchAngleY = aimPunch_y; // 0
	}
}

inline VOID Cheats::JumpShot()
{
	return VOID();
}

// Defination for Triggerbot
inline VOID Cheats::BeginTriggerBot()
{
	if (game.EntityIndex > 0)
	{
		uintptr_t entityListEntry = Driver::RPM<uintptr_t>(game.EntityList + 0x8 * (game.EntityIndex >> 9) + 0x10);
		uintptr_t entity = Driver::RPM<uintptr_t>(entityListEntry + 120 * (game.EntityIndex & 0x1FF));

		int entityTeam = Driver::RPM<int>(entity + Offsets::m_iTeamNum);
		int entityHealth = Driver::RPM<int>(entity + Offsets::m_iHealth);

		if (Data::TriggerBot::m_bEnableTeamCheck == TRUE)
		{
			if (entityTeam != localplayer.Team && entityHealth > 0)
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

// Triggerbot Thread
inline std::thread triggerbot_thread([] {
	while (Flags::m_bIsRunning) {
		if (Data::TriggerBot::m_bEnableTriggerBot == TRUE)
		{
			if (Data::TriggerBot::m_bEnableHotKey)
			{
				if (GetAsyncKeyState(Data::TriggerBot::m_iCurrentKey))
					cheats.BeginTriggerBot();
			}
			else
			{
				cheats.BeginTriggerBot();
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	});