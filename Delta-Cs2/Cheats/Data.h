#pragma once
#include <Globals/Globals.h>
#include <Maths/Vector.hpp>
#include <SDK/CPlayer.h>

inline ImVec4 RgbToImVec4(int r, int g, int b, int a)
{
	return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

// Cheat Datas
namespace Data
{
	inline String folderName = "configs";
	inline String fileName = "config";

	namespace Game
	{
		inline ImVec4 m_clTerroristColor = RgbToImVec4(234, 209, 139, 255);
		inline ImVec4 m_clCounterTerroristColor = RgbToImVec4(182, 212, 238, 255);
		inline ImVec4 m_clSpectatorColor = RgbToImVec4(255, 255, 255, 255);

		inline bool m_bCrosshair = FALSE;
		inline float  m_flCrosshairSize = 10.0f;
		inline ImVec4 m_clCrosshairColor = RgbToImVec4(255, 255, 255, 255);

		inline float  m_flSensitivity = cPlayer.Sensitivity;
	}

	namespace Esp
	{
		inline bool m_bPlayerEsp = TRUE;
		inline bool m_bWorldEsp = TRUE;
		inline bool m_bBombEsp = TRUE;

		namespace Player
		{
			// Features
			inline bool  m_bEnableBox = TRUE;
			inline bool  m_bEnableLines = FALSE;
			inline bool  m_bEnableNames = TRUE;
			inline bool  m_bEnableDistance = FALSE;
			inline bool  m_bEnableHealthBar = TRUE;
			inline bool  m_bEnableHealthText = FALSE;
			inline bool  m_bEnableArmorBar = FALSE;
			inline bool  m_bEnableBones = TRUE;
			inline bool  m_bEnableBonesJoints = TRUE;
			inline bool  m_bBoneHeadFilled = FALSE;

			// others
			inline bool  m_bBoxFilled = TRUE;
			inline bool  m_bTeamCheck = TRUE;
			inline bool  m_bDormantCheck = TRUE;
			inline bool  m_bBonesOnDeadEntity = TRUE;

			// Esp Customizer Vars
			inline float m_flBoxUnfilledThickness = 2.0f;
			inline float m_flLinesThickness = 2.0f;
			inline float m_flBonesThickness = 2.0f;
			inline float m_flJointRadius = 2.0f;
			inline float m_flDistanceTextSize = 15.0f;
			inline float m_flHealthTextSize = 15.0f;
			inline float m_flNameTextSize = 15.0f;
			inline float m_flLineEndPointDisplayDistance = 1000.0f;

			inline ImVec4 m_clBoxFilledColor = RgbToImVec4(255, 255, 255, 96);
			inline ImVec4 m_clBoxUnfilledColor = RgbToImVec4(10, 10, 10, 255);
			inline ImVec4 m_clLineColor = RgbToImVec4(117, 255, 0, 255);
			inline ImVec4 m_clNameColor = RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clArmorBarColor = RgbToImVec4(182, 212, 238, 255);
			inline ImVec4 m_clDistanceTextColor = RgbToImVec4(16, 224, 221, 255);
			inline ImVec4 m_clHealthBarColor = RgbToImVec4(0, 255, 0, 255);
			inline ImVec4 m_clBoneColor = RgbToImVec4(10, 10, 10, 255);
			inline ImVec4 m_clBoneHeadColor = RgbToImVec4(10, 10, 10, 255);
			inline ImVec4 m_clBoneJointsColor = RgbToImVec4(255, 255, 255, 255);

			inline int m_iCurrentLinePosIndex = 0;
			inline const char* m_AvailableSnapLinesPos[] = { "Top", "Center", "Bottom" };
			inline Vector2 m_vecCurrentlinePos;
		}

		namespace Bomb
		{
			inline bool m_bEnableC4Box = TRUE;
			inline bool m_bEnableC4DistanceText = TRUE;
			inline bool m_bEnableC4Lines = FALSE;

			inline ImVec4 m_clDistanceTextColor = RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clPlantedC4BoxColor = RgbToImVec4(255, 0, 0, 30.0f);
			inline ImVec4 m_clDroppedC4BoxColor = RgbToImVec4(0, 255, 0, 30.0f);
			inline ImVec4 m_clC4LineColor		= RgbToImVec4(0, 255, 0, 128);

			inline float m_flBoxThickness = 2.0f;
			inline float m_flLineThickness = 2.0f;

			inline int m_iCurrentLinePosIndex = 0;
			inline const char* m_AvailableSnapLinesPos[] = { "Top", "Center", "Bottom" };
			inline Vector2 m_vecCurrentlinePos;
		}

		namespace World
		{
			inline bool m_bEnableDroppedWeaponEsp = FALSE;
			inline bool m_bEnableProjectilesEsp = TRUE;
			inline bool m_bEnableChickenEsp = TRUE;
			inline bool m_bEnableHostagesEsp = FALSE;

			inline ImVec4 m_clWeaponEspTextColor = RgbToImVec4(19, 0, 255, 255);
			inline ImVec4 m_clWeaponEspTextStrokeColor = RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clProjectilesEspTextColor = RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clProjectilesEspTextStrokeColor = RgbToImVec4(255, 0, 0, 255);
			inline ImVec4 m_clChickenEspTextColor = RgbToImVec4(27, 14, 251, 255);
			inline ImVec4 m_clChickenEspTextStrokeColor = RgbToImVec4(255, 0, 0, 255);
			inline ImVec4 m_clWorldEntitiesBoxColor = RgbToImVec4(255, 255, 255, 255);
		}
	}

	namespace Aimbot
	{
		inline bool m_bAimbot = TRUE;
		inline bool m_bEnableHotKey = TRUE;
		inline bool m_bTeamCheck = TRUE;

		inline bool m_bFovBased = TRUE;
		inline bool m_bShowFovCircle = TRUE;
		inline float m_flFov = 60.0f;
		inline float m_flFovCircleThickness = 1.0f;
		inline ImVec4 m_clFovCircleColor = RgbToImVec4(255, 255, 255, 255);

		inline bool m_bAddSmoothness = FALSE;
		inline float m_flSmoothness = 0.5f;

		inline int m_iCurrentKey = 0x06;

		inline const char* m_AimPositions[] = {
			"Head",
			"Penis",
			"Neck",
			"Chest",
			"Stomach",
			"LShoulder",
			"LArm",
			"LHand",
			"RShoulder",
			"RArm",
			"RHand",
			"LThigh",
			"LCalf",
			"LFoot",
			"RThigh",
			"RCalf",
			"RFoot",
		};
		inline static int m_iCurrentAimPosIndex = 0; // Index of the currently selected item
	}

	namespace Memory
	{
		inline bool m_bEnableAntiflash = FALSE;
		inline bool m_bEnableNoSky = FALSE;
		inline bool m_bEnableNoSpread = FALSE;
		inline bool m_bEnableTPV = FALSE;
		inline bool m_bEnableMapView = FALSE;
		inline bool m_bEnableBhop = FALSE;
		inline bool m_bEnableFovChanger = FALSE;
		inline bool m_bEnableSensiChanger = FALSE;

		inline float m_flFlashAlpha = 30.0f;
	}

	namespace Rcs
	{
		inline bool  m_bRcs = TRUE;
		inline float m_flOldPunchAngleX = 0.0f;
		inline float m_flOldPunchAngleY = 0.0f;
	}

	namespace JumpShot
	{
		inline bool m_bJumpShot = TRUE;
	}

	namespace Fov
	{
		inline UINT16 m_iDesiredFov;
		inline int m_iDefaultFov = 60;
	}

	namespace TriggerBot
	{
		inline bool m_bEnableTriggerBot = TRUE;
		inline bool m_bEnableHotKey = TRUE;
		inline bool m_bEnableTeamCheck = TRUE;
		inline static int  m_iCurrentKey = 0xA0;
	}

	namespace AntiAfk
	{
		inline bool m_bEnableAntiAfk = TRUE;
		inline int m_iMaxIdleDuration = 300; // seconds
	}

}

