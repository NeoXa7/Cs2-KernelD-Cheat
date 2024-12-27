#pragma once
#include <Globals/Globals.h>
#include <Maths/Vector.hpp>
#include <SDK/Readers.h>

inline ImVec4 RgbToImVec4(int r, int g, int b, int a)
{
	return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

namespace Data
{
	namespace Game
	{
		inline ImVec4 m_clTerroristColor			= RgbToImVec4(234, 209, 139, 255);
		inline ImVec4 m_clCounterTerroristColor		= RgbToImVec4(182, 212, 238, 255);
		inline ImVec4 m_clSpectatorColor			= RgbToImVec4(255, 255, 255, 255);

		inline bool	  m_bCrosshair			= FALSE;
		inline float  m_flCrosshairSize		= 10.0f;
		inline ImVec4 m_clCrosshairColor	= RgbToImVec4(255, 255, 255, 255); // Default Crosshair Color;

		inline float  m_flSensitivity		= localplayer.Sensitivity;
	}

	namespace Esp
	{
		inline bool m_bPlayerEsp	= TRUE;
		inline bool m_bWorldEsp		= TRUE;
		inline bool m_bBombEsp		= TRUE;

		namespace Player
		{
			// Features
			inline bool  m_bEnableBox				= TRUE;
			inline bool  m_bEnableLines				= TRUE;
			inline bool  m_bEnableNames				= TRUE;
			inline bool  m_bEnableDistance			= TRUE;
			inline bool  m_bEnableHealthBar			= TRUE;
			inline bool  m_bEnableHealthText		= TRUE;
			inline bool  m_bEnableArmorBar			= TRUE;
			inline bool  m_bEnableBones				= TRUE;
			inline bool  m_bEnableBonesJoints		= TRUE;
			inline bool  m_bBoneHeadFilled			= TRUE;

			// others
			inline bool  m_bBoxFilled				= TRUE;
			inline bool  m_bTeamCheck				= TRUE;
			inline bool  m_bDormantCheck			= TRUE;
			inline bool  m_bBonesOnDeadEntity		= TRUE;

			// Esp Customizer Vars
			inline float m_flBoxUnfilledThickness	= 2.0f;
			inline float m_flLinesThickness			= 2.0f;
			inline float m_flBonesThickness			= 2.0f;
			inline float m_flJointRadius			= 2.0f;
			inline float m_flDistanceTextSize		= 15.0f;
			inline float m_flHealthTextSize			= 15.0f;
			inline float m_flNameTextSize			= 15.0f;
			inline float m_flLineEndPointDisplayDistance = 3000.0f;

			inline  int m_iBoxOpacity	= 66;

			inline ImVec4 m_clBoxFilledColor		= RgbToImVec4(96, 3, 182, m_iBoxOpacity);
			inline ImVec4 m_clBoxUnfilledColor		= RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clLineColor				= RgbToImVec4(117, 255, 0, 255);
			inline ImVec4 m_clNameColor				= RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clArmorBarColor			= RgbToImVec4(182, 212, 238, 255);
			inline ImVec4 m_clDistanceTextColor		= RgbToImVec4(0, 147, 255, 255);
			inline ImVec4 m_clHealthBarColor		= RgbToImVec4(0, 255, 0, 255);
			inline ImVec4 m_clBoneColor				= RgbToImVec4(7, 9, 3, 255);
			inline ImVec4 m_clBoneHeadColor			= RgbToImVec4(255, 0, 0, 255);
			inline ImVec4 m_clBoneJointsColor		= RgbToImVec4(255, 0, 0, 255);

			inline int		   m_iCurrentLinePosIndex	 = 2;
			inline const char* m_AvailableSnapLinesPos[] = { "Top", "Center", "Bottom" };
			inline Vector2	   m_vecCurrentlinePos;
		}

		namespace Bomb
		{
			inline bool m_bEnableC4Box			= TRUE;
			inline bool m_bEnableC4DistanceText = TRUE;
			inline bool m_bEnableC4Lines		= FALSE;

			inline int m_iBoxOpacity			= 30.0f;

			inline ImVec4 m_clDistanceTextColor = RgbToImVec4(255, 255, 255, 255);
			inline ImVec4 m_clPlantedC4BoxColor = RgbToImVec4(255, 0, 0, m_iBoxOpacity);
			inline ImVec4 m_clDroppedC4BoxColor = RgbToImVec4(0, 255, 0, m_iBoxOpacity);
			inline ImVec4 m_clC4LineColor		= RgbToImVec4(0, 255, 0, 128);

			inline float m_flBoxThickness	= 2.0f;
			inline float m_flLineThickness	= 2.0f;

			inline int		   m_iCurrentLinePosIndex = 0;
			inline const char* m_AvailableSnapLinesPos[] = { "Top", "Center", "Bottom" };
			inline Vector2	   m_vecCurrentlinePos;
		}

		namespace World
		{
			inline bool m_bEnableDroppedWeaponEsp	= TRUE;
			inline bool m_bEnableProjectilesEsp		= TRUE;
			inline bool m_bEnableChickenEsp			= TRUE;
			inline bool m_bEnableHostagesEsp		= FALSE;

			inline ImVec4 m_clWeaponEspTextColor			= RgbToImVec4(255, 0, 0, 255);
			inline ImVec4 m_clWeaponEspTextStrokeColor		= RgbToImVec4(0, 91, 255, 255);
			inline ImVec4 m_clProjectilesEspTextColor		= RgbToImVec4(117, 0, 255, 255);
			inline ImVec4 m_clProjectilesEspTextStrokeColor = RgbToImVec4(0, 255, 243, 255);
			inline ImVec4 m_clChickenEspTextColor			= RgbToImVec4(27, 14, 251, 255);
			inline ImVec4 m_clChickenEspTextStrokeColor		= RgbToImVec4(255, 0, 0, 255);
			inline ImVec4 m_clWorldEntitiesBoxColor			= RgbToImVec4(255, 255, 255, 255);
		}
	}

	namespace Aimbot
	{
		inline bool m_bAimbot		= FALSE;
		inline bool m_bEnableHotKey = TRUE;
		inline bool m_bTeamCheck	= TRUE;
		inline const char* m_HotkeyOptions[] = {
			"X2_Mouse Button",
			"X1_Mouse Button",
			"Right Mouse Button",
			"Left Shift",
			"Left CTRL",
			"Left Alt"
		};
		inline static int m_iCurrentHotkeyIndex = 0; // Index of the currently selected item
		inline int m_iCurrentKey = 0x06;

		inline const char* m_AimPositions[] = {
			"Head",
			"Penis",
			"Neck",
			"Chest",
			"Stomach"
		};
		inline static int m_iCurrentAimPosIndex = 0; // Index of the currently selected item
	}

	namespace Memory
	{
		inline bool m_bEnableAntiflash		= FALSE;
		inline bool m_bEnableNoSky			= FALSE;
		inline bool m_bEnableNoSpread		= FALSE;
		inline bool m_bEnableTPV			= FALSE;
		inline bool m_bEnableMapView		= FALSE;
		inline bool m_bEnableBhop			= FALSE;
		inline bool m_bEnableFovChanger		= FALSE;
		inline bool m_bEnableSensiChanger	= FALSE;

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
		inline bool m_bEnableTriggerBot	= TRUE;
		inline bool m_bEnableHotKey		= TRUE;
		inline bool m_bEnableTeamCheck	= TRUE;
		inline const char* m_HotkeyOptions[] = {
			"Left Shift",
			"Left CTRL",
			"Left Alt",
			"X1_Mouse Button",
			"X2_Mouse Button"
		};

		inline static int m_iCurrentHotkeyIndex = 0;
		inline int m_iCurrentKey				= 0xA0;
	}
}