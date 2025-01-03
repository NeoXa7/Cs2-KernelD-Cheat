#pragma once
#include "sdkincs.h"
#include <Cheats/Coords.h>

namespace CPlayerEntities
{
	// Locates all the entities in the game and renders ESP elements to reveal their locations and positions.
	inline VOID ExtraSensoryPreception()
	{
		Vector3 HeadPosition = cEntities->Position + Vector3{ 0.0f,0.0f,72.0f };

		Vector2 EntitiesScreenPosition, EntitiesHeadScreenPos;

		Data::Esp::Player::m_clHealthBarColor = cEntities->GetColorHealth();

		if (cView.Project3DWorldTo2D(cEntities->Position, EntitiesScreenPosition, cGame.ViewMatrix) &&  // Entities W2S Position;
			cView.Project3DWorldTo2D(HeadPosition, EntitiesHeadScreenPos, cGame.ViewMatrix)) // Entities W2S Head Position;
		{
			float boxHeight = std::fabs(EntitiesHeadScreenPos.y - EntitiesScreenPosition.y);
			float boxWidth = boxHeight * 0.6f;

			Vector2 TopLeft(EntitiesScreenPosition.x - boxWidth / 2, EntitiesHeadScreenPos.y);
			Vector2 TopRight(EntitiesScreenPosition.x + boxWidth / 2 + 12.0f, EntitiesHeadScreenPos.y);
			Vector2 BottomRight(EntitiesScreenPosition.x + boxWidth / 2, EntitiesScreenPosition.y);

			if (cEntities->Dead)
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

				if ((cPlayer.Position - cEntities->Position).Magnitude() / GAME_METRIC_UNITS < Data::Esp::Player::m_flLineEndPointDisplayDistance)
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
				float distanceFactor = 1.0f / (cPlayer.Position - cEntities->Position).Magnitude() / GAME_METRIC_UNITS; // Scale the font inversely with distance
				float scaledFontSize = min(Data::Esp::Player::m_flNameTextSize * distanceFactor, 15.0f); // Minimum font size

				Draw::TextWithStroke(
					cEntities->Names,
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
					cEntities->Health,
					Data::Esp::Player::m_clHealthBarColor,
					2.0f,
					4.0f
				);
			}

			// Draw the Health text
			if (Data::Esp::Player::m_bEnableHealthText == TRUE)
			{
				char healthText[16];
				snprintf(healthText, sizeof(healthText), "[%d]", cEntities->Health);

				// Calculate the position for the health text to be just above the health bar
				Vector2 healthBarTopLeft(TopLeft.x - 6.0f - 5.0f, BottomRight.y - (BottomRight.y - TopLeft.y));
				Vector2 healthTextPos(healthBarTopLeft.x - 35.0f, healthBarTopLeft.y);

				float distanceFactor = 1.0f / (cPlayer.Position - cEntities->Position).Magnitude() / GAME_METRIC_UNITS; // Scale the font inversely with distance
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
				if (cEntities->Team == 2)
				{
					Data::Esp::Player::m_clArmorBarColor = Data::Game::m_clTerroristColor;
				}
				else if (cEntities->Team == 3)
				{
					Data::Esp::Player::m_clArmorBarColor = Data::Game::m_clCounterTerroristColor;
				}

				Draw::HealthBar
				(
					TopRight,
					BottomRight,
					cEntities->Armor,
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
				snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", (cPlayer.Position - cEntities->Position).Magnitude() / GAME_METRIC_UNITS);

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

	// Identifies all the targets in the game and automatically adjusts the aim to align with their positions.
	inline VOID Aimbot(UINTPTR Client)
	{
		cPlayer.READ(Client);
		if (Data::Aimbot::m_bShowFovCircle)
			Draw::Circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Data::Aimbot::m_flFov, Data::Aimbot::m_clFovCircleColor, Data::Aimbot::m_flFovCircleThickness);

		if (cEntities->Dead)
			return;
		
		if (Data::Aimbot::m_bTeamCheck)
		{
			if (cEntities->Team == cPlayer.Team)
				return;
		}
			

		Vector3 TargetPosition3D;

		// RIP SWITCH
		switch (Data::Aimbot::m_iCurrentAimPosIndex)
		{
		case 0: TargetPosition3D = Coords::GetHeadCoordinates3D(); break;
		case 1: TargetPosition3D = Coords::GetPenisCoordinates3D(); break;
		case 2: TargetPosition3D = Coords::GetNeckCoordinates3D(); break;
		case 3: TargetPosition3D = Coords::GetChestCoordinates3D(); break;
		case 4: TargetPosition3D = Coords::GetStomachCoordinates3D(); break;
		default: TargetPosition3D = Coords::GetHeadCoordinates3D(); break;
		}

		/*
		
		//case 5: TargetPosition3D = AimbotCoords::GetLShoulderCoordinates3D(); break;
		//case 6: TargetPosition3D = AimbotCoords::GetLArmCoordinates3D(); break;
		//case 7: TargetPosition3D = AimbotCoords::GetLHandCoordinates3D(); break;

		//case 8: TargetPosition3D = AimbotCoords::GetRShoulderCoordinates3D(); break;
		//case 9: TargetPosition3D = AimbotCoords::GetRArmCoordinates3D(); break;
		//case 10: TargetPosition3D = AimbotCoords::GetRHandCoordinates3D(); break;

		//case 11: TargetPosition3D = AimbotCoords::GetLThighCoordinates3D(); break;
		//case 12: TargetPosition3D = AimbotCoords::GetLCalfCoordinates3D(); break;
		//case 13: TargetPosition3D = AimbotCoords::GetLFootCoordinates3D(); break;

		//case 14: TargetPosition3D = AimbotCoords::GetRThighCoordinates3D(); break;
		//case 15: TargetPosition3D = AimbotCoords::GetRCalfCoordinates3D(); break;
		//case 16: TargetPosition3D = AimbotCoords::GetRFootCoordinates3D(); break;

		*/

		Vector2 TargetPosition2D;
		if (!cView.Project3DWorldTo2D(TargetPosition3D, TargetPosition2D, cGame.ViewMatrix))
			return;

		Vector2 PixelCalculation2D = TargetPosition2D - ScreenCenter; // Getting Entity Distance from the Crosshair or Center of Screen
		Float PixelDistance = PixelCalculation2D.Magnitude();

		Vector3 PlayerView3D = cPlayer.Position + cPlayer.View;
		Vector3 EntityView3D = cEntities->Position + cEntities->View;

		Vector2 NewAngles2D = cAngle.CalculateAngles(PlayerView3D, TargetPosition3D);
		Vector3 NewAngles3D = Vector3(NewAngles2D.y, NewAngles2D.x, 0.0f);

		if (Data::Aimbot::m_bFovBased && PixelDistance < Data::Aimbot::m_flFov)
		{
			if (Data::Aimbot::m_bEnableHotKey)
			{
				if (GetAsyncKeyState(Data::Aimbot::m_iCurrentKey))
					cAngle.SetViewAngles(Client, NewAngles3D);
			}
			else if (!Data::Aimbot::m_bEnableHotKey)
			{
				cAngle.SetViewAngles(Client, NewAngles3D);
			}
		}
		else if (!Data::Aimbot::m_bFovBased)
		{
			Data::Aimbot::m_bShowFovCircle = FALSE;
			if (Data::Aimbot::m_bEnableHotKey)
			{
				if (GetAsyncKeyState(Data::Aimbot::m_iCurrentKey))
					cAngle.SetViewAngles(Client, NewAngles3D);
			}
			else if (!Data::Aimbot::m_bEnableHotKey)
			{
				cAngle.SetViewAngles(Client, NewAngles3D);
			}
		}
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