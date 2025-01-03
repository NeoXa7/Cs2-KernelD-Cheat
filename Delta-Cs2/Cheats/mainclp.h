#include "sdkincs.h"
#include <Cheats/CPlayerEntities.h>
#include <Cheats/CLocalPlayer.h>
#include <Cheats/CWorld.h>
#include <Cheats/Coords.h>

// Main Class for Cheats
class Cheats
{
public:
	// Loop for Player Entities (Iterates Over 0 to 64 Entities)
	// Draws Player and Bomb Esp, Aimbot, Triggerbot (Runs on Seperate Thread Not in this Loop)
	VOID BeginPlayerEntityLoop(uintptr_t ClientDll, uintptr_t MatchmakingDll)
	{
		cGame.READ(ClientDll, MatchmakingDll);
		cPlayer.READ(ClientDll);

		for (int i = 0; i < 64; i++)
		{
			UINTPTR ListEntry = Driver::RPM<UINTPTR>(cGame.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!ListEntry)
				continue;

			UINTPTR CCSPlayerController = Driver::RPM<UINTPTR>(ListEntry + 120 * (i & 0x1FF));
			if (!CCSPlayerController)
				continue;

			UINTPTR PawnHandle = Driver::RPM<UINTPTR>(CCSPlayerController + Offsets::m_hPlayerPawn);
			if (!PawnHandle)
				continue;

			UINTPTR ListEntry2 = Driver::RPM<UINTPTR>(cGame.EntityList + 0x8 * ((PawnHandle & 0x7FFF) >> 9) + 16);
			if (!ListEntry2)
				continue;

			UINTPTR CCSPlayerPawn = Driver::RPM<UINTPTR>(ListEntry2 + 120 * (PawnHandle & 0x1FF));
			if (!CCSPlayerPawn)
				continue;

			cEntities->READ(CCSPlayerPawn, CCSPlayerController);
			cGame.READ(ClientDll, MatchmakingDll);

			if (CCSPlayerPawn == cPlayer.Pawn) // Ensures that the cheat logic for entities doesn't apply to ourselves or the local player.
				continue;

			// Visual Cheats
			if (Flags::VisualCheats == ENABLED)
			{
				// Player Esp
				{
					if (Data::Esp::m_bPlayerEsp == TRUE)
					{
						if (Data::Esp::Player::m_bTeamCheck == TRUE)
						{
							if (cEntities->Team == cPlayer.Team)
								continue;
						}

						CPlayerEntities::ExtraSensoryPreception();

						// Bone Esp
						if (Data::Esp::Player::m_bEnableBones == TRUE)
						{
							if (Data::Esp::Player::m_bBonesOnDeadEntity == FALSE)
							{
								if (cEntities->Health <= 0)
									return;
							}

							Draw::Bones(
								cEntities->BoneMatrix, cEntities->Position, cGame.ViewMatrix, Data::Esp::Player::m_clBoneColor,
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
						CWorld::BombESP();
					}
				}

			}

			// Aim Cheats
			if (Flags::AimCheats == ENABLED)
			{
				if (Data::Aimbot::m_bAimbot)
				{
					CPlayerEntities::Aimbot(ClientDll);
				}				
			}
		}
	}

	// Seperate Loop for World Esp (Iterates Over 64 - 1024 Entities)
	// Displays the locations of dropped weapons and projectiles in the game using ESP elements.
	VOID BeginWorldEntitiesLoop(uintptr_t ClientDll, uintptr_t MatchmakingDll)
	{
		if (Flags::VisualCheats == ENABLED && Data::Esp::m_bWorldEsp)
		{
			cGame.READ(ClientDll, MatchmakingDll);
			for (int i = 64; i < 1024; i++)
			{
				UINTPTR ItemEntityListEntry = Driver::RPM<UINTPTR>(cGame.EntityList + 8LL * ((i & 0x7FFF) >> 9) + 16);
				if (!ItemEntityListEntry)
					continue;

				UINTPTR ItemEntity = Driver::RPM<UINTPTR>(ItemEntityListEntry + 120LL * (i & 0x1FF)); // Item Entity
				if (!ItemEntity)
					continue;

				UINTPTR ItemEntityNode = Driver::RPM<UINTPTR>(ItemEntity + Offsets::m_pGameSceneNode); // Item Entity Node
				Vector3 ItemEntityOrigin = Driver::RPM<Vector3>(ItemEntityNode + Offsets::m_vecAbsOrigin); // Item Entity Origin


				Vector2 World2DScreenProjection;
				if (!cView.Project3DWorldTo2D(ItemEntityOrigin, World2DScreenProjection, cGame.ViewMatrix))
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
								if (!cView.Project3DWorldTo2D(ChickenHeight, ChickenScreenPos, cGame.ViewMatrix))
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
	
	// Runs all the Cheats for Localplayer
	// Flashalpha Override, Fov Changer, Jumpshot, Bhop
	VOID BeginLocalCheats(uintptr_t Client)
	{
		if (Flags::MemoryCheats == ENABLED)
		{
			cPlayer.READ(Client);

			// Antiflash
			if (Data::Memory::m_bEnableAntiflash == TRUE)
			{
				CLocalPlayer::ChangeFlashAlpha();
			}

			// Fov Changer
			if (Data::Memory::m_bEnableFovChanger == TRUE)
			{
				CLocalPlayer::ChangeFieldOfView();
			}

			// Bunny Hop
			if (Data::Memory::m_bEnableBhop == TRUE)
			{
				CLocalPlayer::BunnyHop(Client);
			}
		}
		
		if (Flags::AimCheats == ENABLED)
		{
			cPlayer.READ(Client);

			if (Data::Rcs::m_bRcs == TRUE)
			{
				CLocalPlayer::StandaloneRecoilControlSystem();
			}

			if (Data::JumpShot::m_bJumpShot == TRUE)
			{
				CLocalPlayer::JumpShot();
			}
		}

		if (Data::AntiAfk::m_bEnableAntiAfk)
		{
			CLocalPlayer::AntiAFK(Client);
		}
	}

}; inline Cheats cheats;

// Triggerbot Thread
inline std::thread triggerbot_thread([] {
	while (Flags::m_bIsRunning) {
		if (Data::TriggerBot::m_bEnableTriggerBot == TRUE)
		{
			if (Data::TriggerBot::m_bEnableHotKey)
			{
				if (GetAsyncKeyState(Data::TriggerBot::m_iCurrentKey))
					CPlayerEntities::Triggerbot();
			}
			else
			{
				CPlayerEntities::Triggerbot();
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	});
