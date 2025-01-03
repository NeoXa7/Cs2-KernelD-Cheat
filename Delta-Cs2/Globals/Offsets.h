/*
	cs2-dumper (https://github.com/a2x/cs2-dumper)
	An external offset/interface dumper for Counter-Strike 2, with support for both Windows & Linux. Powered by memflow.
*/

#pragma once
#include <cstddef>

inline const char* OffsetsJson = "https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json";
inline const char* ClientDllJson = "https://github.com/a2x/cs2-dumper/raw/main/output/client_dll.json";
inline const char* ButtonsJson = "https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json";

namespace Offsets
{
	// buttons.hpp/client.dll
	inline std::ptrdiff_t attack = 0x184E4D0;
	inline std::ptrdiff_t attack2 = 0x184E560;
	inline std::ptrdiff_t back = 0x184E7A0;
	inline std::ptrdiff_t duck = 0x184EA70;
	inline std::ptrdiff_t forward = 0x184E710;
	inline std::ptrdiff_t jump = 0x18619D0;
	inline std::ptrdiff_t left = 0x184E830;
	inline std::ptrdiff_t lookatweapon = 0x1A5E1A0;
	inline std::ptrdiff_t reload = 0x184E440;
	inline std::ptrdiff_t right = 0x184E8C0;
	inline std::ptrdiff_t showscores = 0x1A5E080;
	inline std::ptrdiff_t sprint = 0x184E3B0;
	inline std::ptrdiff_t turnleft = 0x184E5F0;
	inline std::ptrdiff_t turnright = 0x184E680;
	inline std::ptrdiff_t use = 0x184E950;
	inline std::ptrdiff_t zoom = 0x1A5E110;

	// offsets.hpp/client.dll
	inline std::ptrdiff_t dwCSGOInput = 0x1A89340;
	inline std::ptrdiff_t dwEntityList = 0x1A146E8;
	inline std::ptrdiff_t dwGameEntitySystem = 0x1B37E58;
	inline std::ptrdiff_t dwGameEntitySystem_highestEntityIndex = 0x20F0;
	inline std::ptrdiff_t dwGameRules = 0x1A7AF28;
	inline std::ptrdiff_t dwGlobalVars = 0x185C9B0;
	inline std::ptrdiff_t dwGlowManager = 0x1A7A668;
	inline std::ptrdiff_t dwLocalPlayerController = 0x1A64E80;
	inline std::ptrdiff_t dwLocalPlayerPawn = 0x1868CC8;
	inline std::ptrdiff_t dwPlantedC4 = 0x1A84F90;
	inline std::ptrdiff_t dwPrediction = 0x1868B60;
	inline std::ptrdiff_t dwSensitivity = 0x1A7BC48;
	inline std::ptrdiff_t dwSensitivity_sensitivity = 0x40;
	inline std::ptrdiff_t dwViewAngles = 0x1A89710;
	inline std::ptrdiff_t dwViewMatrix = 0x1A7F610;
	inline std::ptrdiff_t dwViewRender = 0x1A7FE20;
	inline std::ptrdiff_t dwWeaponC4 = 0x1A17928;

	// offsets.hpp/matchmaking.dll
	inline std::ptrdiff_t dwGameTypes = 0x1A41B0;
	inline std::ptrdiff_t dwGameTypes_mapName = 0x120;

	// offsets.hpp/engine2.dll
	inline std::ptrdiff_t dwBuildNumber = 0x532BE4;

	// client_dll.hpp/client.dll
	inline std::ptrdiff_t m_sSanitizedPlayerName = 0x770; // CUtlString
	inline std::ptrdiff_t m_iTeamNum = 0x3E3; // uint8
	inline std::ptrdiff_t m_iHealth = 0x344; // int32
	inline std::ptrdiff_t m_ArmorValue = 0x241C; // int32
	inline std::ptrdiff_t m_iPing = 0x740; // uint32
	inline std::ptrdiff_t m_iShotsFired = 0x23FC; // int32
	inline std::ptrdiff_t m_aimPunchAngle = 0x1584; // QAngle
	inline std::ptrdiff_t m_vOldOrigin = 0x1324; // Vector
	inline std::ptrdiff_t m_vecViewOffset = 0xCB0; // CNetworkViewOffsetVector
	inline std::ptrdiff_t m_vecAbsVelocity = 0x3F0; // Vector
	inline std::ptrdiff_t m_bIsScoped = 0x23E8; // bool	
	inline std::ptrdiff_t m_pGameSceneNode = 0x328; // CGameSceneNode*
	inline std::ptrdiff_t m_bWarmupPeriod = 0x41; // bool
	inline std::ptrdiff_t m_bBombDropped = 0x9A4; // bool
	inline std::ptrdiff_t m_bBombPlanted = 0x9A5; // bool
	inline std::ptrdiff_t m_bBeingDefused = 0xFCC; // bool
	inline std::ptrdiff_t m_flFlashBangTime = 0x13F8; // float32
	inline std::ptrdiff_t m_iIDEntIndex = 0x1458; // CEntityIndex
	inline std::ptrdiff_t m_pCameraServices = 0x11E0; // CPlayer_CameraServices*
	inline std::ptrdiff_t m_bTerroristTimeOutActive = 0x4D; // bool
	inline std::ptrdiff_t m_bCTTimeOutActive = 0x4E; // bool
	inline std::ptrdiff_t m_vecAbsOrigin = 0xD0; // Vector
	inline std::ptrdiff_t m_nBombSite = 0xF94; // int32
	inline std::ptrdiff_t m_fFlags = 0x3EC; // uint32
	inline std::ptrdiff_t m_hOwnerEntity = 0x440; // CHandle<C_BaseEntity>
	inline std::ptrdiff_t m_hPlayerPawn = 0x80C; // CHandle<C_CSPlayerPawn>
	inline std::ptrdiff_t m_bHasExploded = 0xFC5; // bool
	inline std::ptrdiff_t m_flDefuseLength = 0xFDC; // float32
	inline std::ptrdiff_t m_bDormant = 0xEF; // bool
	inline std::ptrdiff_t m_groundNormal = 0x1F0; // Vector
	inline std::ptrdiff_t m_iFOV = 0x210; // uint32
	inline std::ptrdiff_t m_flFlashMaxAlpha = 0x1408; // float32
}