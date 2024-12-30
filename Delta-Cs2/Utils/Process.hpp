#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

class Process
{
public:
    DWORD GetProcessID(CONST WCHAR* target_process_name);
    uintptr_t GetModuleBaseAddress(DWORD target_process_id, CONST WCHAR* target_module);
    BOOL IsProcessRunning(DWORD pid_to_check);

};
