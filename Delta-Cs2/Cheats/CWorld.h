#pragma once
#include "sdkincs.h"

namespace CWorld
{
	// Locates the c4 entity in the game and renders ESP elements to reveal the location and position of the bomb.
	inline VOID BombESP()
	{
		Vector3 PlantedC4Pos3D = cC4.GetPlantedC4Position();
		Vector3 DroppedC4Pos3D = cC4.GetDroppedC4Position();
		float C4Width = 30.0f;
		float C4Height = 20.0f;

		switch (Data::Esp::Bomb::m_iCurrentLinePosIndex) {
		case 0: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenTop; break;
		case 1: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenCenter; break;
		case 2: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenBottom; break;
		default: Data::Esp::Bomb::m_vecCurrentlinePos = ScreenBottom; break;
		}

		if (cGame.IsBombPlanted)
		{
			Vector2 Planted_C4_ScreenPos, PlantedC4Height;
			Vector3 PlantedC4HeightPos = PlantedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height };

			if (cView.Project3DWorldTo2D(PlantedC4Pos3D, Planted_C4_ScreenPos, cGame.ViewMatrix) &&
				cView.Project3DWorldTo2D(PlantedC4HeightPos, PlantedC4Height, cGame.ViewMatrix))
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
					float PlantedC4_DistanceInMeters = cC4.GetPC4ToLocalDistance() / GAME_METRIC_UNITS;
					snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", PlantedC4_DistanceInMeters);

					Draw::TextWithStroke(DistTextArray, bottomRightPBP, Data::Esp::Bomb::m_clDistanceTextColor, ImColor(10, 10, 10, 255), 15.0f);
				}
			}
		}

		if (cGame.IsBombDropped)
		{
			Vector2 Dropped_C4_ScreenPos, Dropped_C4_Height;
			Vector3 DroppedC4HeightPos = DroppedC4Pos3D + Vector3{ 0.0f, 0.0f, C4Height };

			if (cView.Project3DWorldTo2D(DroppedC4Pos3D, Dropped_C4_ScreenPos, cGame.ViewMatrix) &&
				cView.Project3DWorldTo2D(DroppedC4HeightPos, Dropped_C4_Height, cGame.ViewMatrix))
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
					float DroppedC4_DistanceInMeters = cC4.GetDC4ToLocalDistance() / GAME_METRIC_UNITS;
					snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", DroppedC4_DistanceInMeters);

					Draw::TextWithStroke(DistTextArray, bottomRightDBP, Data::Esp::Bomb::m_clDistanceTextColor, ImColor(10, 10, 10, 255));
				}
			}
		}
	}


}