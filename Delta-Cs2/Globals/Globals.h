#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <tchar.h>
#include <vector>
#include <thread> 
#include <chrono> 
#include <process.h>
#include <fstream>
#include <map>
#include <unordered_map>
#include <Utils/Process.hpp>
#include <Maths/Vector.hpp>

#define ENABLED         TRUE
#define DISABLED        FALSE
#define SCREEN_WIDTH    GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT   GetSystemMetrics(SM_CYSCREEN)
#define MIN_MENU_WIDTH  680
#define MIN_MENU_HEIGHT 470

inline Vector2 ScreenTop(SCREEN_WIDTH / 2.0f, 0.0f);
inline Vector2 ScreenCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
inline Vector2 ScreenBottom(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);

typedef uintptr_t Pointer;
inline Process cs2;

namespace Flags
{
    inline bool m_bIsRunning = true;
    inline bool m_bIsVisible = true;
    inline bool g_showWarningBox = true;
    inline bool g_showConsole = true;

    // cheats flags;
    inline bool VisualCheats    = ENABLED;
    inline bool MemoryCheats    = ENABLED;
    inline bool MovementCheats  = ENABLED;
    inline bool AimCheats       = ENABLED;
}

namespace CS2
{
    inline DWORD ProcID = cs2.GetProcessID(L"cs2.exe");
    inline uintptr_t ClientDll;
    inline uintptr_t Engine2Dll;
    inline uintptr_t MatchMakingDll;
    inline uintptr_t ServerDll;
}