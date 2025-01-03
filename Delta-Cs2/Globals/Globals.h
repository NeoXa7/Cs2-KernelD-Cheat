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
#include <Maths/ViewMatrix.h>

#define ENABLED TRUE
#define DISABLED FALSE
#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

typedef unsigned long long UINTPTR; // typedef of uintptr_t
typedef void Void;
typedef float Float;
typedef double Double;
typedef int Int;
typedef bool Bool;
typedef std::string String;
typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef view_matrix_t Matrix4x4;
typedef view_matrix_t MATRIX4x4;

constexpr int MIN_MENU_WIDTH = 680;
constexpr int MIN_MENU_HEIGHT = 470;

inline Vector2 ScreenTop(SCREEN_WIDTH / 2.0f, 0.0f);
inline Vector2 ScreenCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
inline Vector2 ScreenBottom(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);

inline Process cs2;

namespace Flags
{
    inline String DataFolderName = "bin";
    inline String DataFileName = "settings.ini";

    inline bool m_bIsRunning = true;
    inline bool m_bIsVisible = true;
    inline bool g_showWarningBox = true;
    inline bool g_showConsole = true;

    // cheats flags;
    inline bool VisualCheats = ENABLED;
    inline bool MemoryCheats = ENABLED;
    inline bool AimCheats = ENABLED;
}

namespace CS2
{
    inline DWORD ProcID = cs2.GetProcessID(L"cs2.exe");
    inline uintptr_t ClientDll;
    inline uintptr_t Engine2Dll;
    inline uintptr_t MatchMakingDll;
    inline uintptr_t ServerDll;
}

namespace Panickey
{
    inline int HIDEMENU = VK_INSERT;
    inline int CLOSEPROGRAM = VK_END;
    inline int VISUAL_CHEATS = VK_F1;
    inline int MEMORY_CHEATS = VK_F2;
    inline int AIM_CHEATS = VK_F3;
}