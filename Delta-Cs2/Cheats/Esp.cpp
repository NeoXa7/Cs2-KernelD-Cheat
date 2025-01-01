#include <Cheats/CPlayerEntities.h>

// Declared inside CEntites.h and Defined here because this function was long
VOID CPlayerEntities::ExtraSensoryPreception()
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

		if (cEntities->IsDead)
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