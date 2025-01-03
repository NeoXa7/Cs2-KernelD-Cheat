#pragma once
#include "sdkincs.h"

namespace CLocalPlayer
{
	// Changes Flash Alpha (Slider provided to modify the flash Alpha)
	inline VOID ChangeFlashAlpha()
	{
		Driver::WPM<Float>(cPlayer.Pawn + Offsets::m_flFlashMaxAlpha, Data::Memory::m_flFlashAlpha);
	}

	// Changes Player Field of View for better and unfair advantage of wide increased view
	inline VOID ChangeFieldOfView()
	{
		UINT16 m_iDesiredFov = (UINT16)Data::Fov::m_iDefaultFov;
		UINT16 currentFov = Driver::RPM<UINT64>(cGame.CameraServices + Offsets::m_iFOV);

		if (cPlayer.IsScoped)
			return;

		if (currentFov != m_iDesiredFov)
		{
			Driver::WPM<UINT64>(cGame.CameraServices + Offsets::m_iFOV, m_iDesiredFov);
		}
	}

	// Detects when the player is in the air and automatically performs a jump to enable bunny hopping.
	inline VOID BunnyHop(UINTPTR Client)
	{
		if (GetAsyncKeyState(VK_SPACE) < 0)
		{
			if (cPlayer.Flag == STANDING || cPlayer.Flag == CROUCHING)
			{
				Driver::WPM<Int>(Client + Offsets::jump, PLUSJUMP);
				Sleep(10);
				Driver::WPM<Int>(Client + Offsets::jump, MINUSJUMP);
			}
		}
	}

	// Stabilizes the player's aim by automatically compensating for recoil when firing, providing smoother shots.
	inline VOID StandaloneRecoilControlSystem()
	{
		float aimPunch_x = cPlayer.AimPunchAngle;
		float aimPunch_y = Driver::RPM<Float>(cPlayer.Pawn + cPlayer.AimPunchAngle + 0x4);

		if (cPlayer.IsShotsFired > 1)
		{
			auto delta_x = (aimPunch_x - Data::Rcs::m_flOldPunchAngleX) * -1.0;
			auto delta_y = (aimPunch_y - Data::Rcs::m_flOldPunchAngleY) * -1.0;
			auto mouse_x = Int((delta_y * 2.0 / cPlayer.Sensitivity) / -0.022);
			auto mouse_y = Int((delta_x * 2.0 / cPlayer.Sensitivity) / 0.022);

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

	// Automatically fires when the player reaches the maximum jump height, ensuring a perfect shot during a jump.
	inline VOID JumpShot()
	{
		if (cPlayer.Flag == INAIR && GetAsyncKeyState(VK_LSHIFT) < 0 && cPlayer.Velocity.z > 18.0f)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			Mouse::Click::LMB();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}

	// Anti-AFK functionality
	inline VOID AntiAFK(UINTPTR Client)
	{
		static std::chrono::steady_clock::time_point lastMovementTime = std::chrono::steady_clock::now();
		static Vector3 lastPosition = cPlayer.Position;
		static bool isIdle = false;

		if (cPlayer.Position.x == lastPosition.x)
		{
			if (!isIdle)
			{
				lastMovementTime = std::chrono::steady_clock::now();
				isIdle = true;
			}
			else
			{
				auto duration = std::chrono::steady_clock::now() - lastMovementTime;
				if (duration > std::chrono::seconds(Data::AntiAfk::m_iMaxIdleDuration))
				{
					Mouse::Click::LMB();
					Mouse::Click::RMB();
					Keyboard::SendKeyPress(VK_SPACE);
					//Keyboard::SendKeyPress(0x57); // W
					//Keyboard::SendKeyPress(0x41); // A
					//Keyboard::SendKeyPress(0x53); // S
					//Keyboard::SendKeyPress(0x44); // D

					//Driver::WPM<BYTE>(Client+ Offsets::forward, ????);
				}
			}
		}
		else
		{
			// Player is not idle, reset tracking
			lastPosition = cPlayer.Position;
			isIdle = false;
		}
	}

}