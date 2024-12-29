#include <Utils/Process.hpp>


DWORD Process::GetProcessID(CONST WCHAR* target_process_name)
{
    DWORD processID = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W processEntry; // Use PROCESSENTRY32W for wide characters
        processEntry.dwSize = sizeof(PROCESSENTRY32W);
        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                if (_wcsicmp(processEntry.szExeFile, target_process_name) == 0) {
                    processID = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }
    return processID;
}

uintptr_t Process::GetModuleBaseAddress(DWORD target_process_id, CONST WCHAR* target_module)
{
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, target_process_id);
    if (snapshotHandle == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    MODULEENTRY32W moduleEntry = { };
    moduleEntry.dwSize = sizeof(MODULEENTRY32W);

    if (Module32FirstW(snapshotHandle, &moduleEntry)) {

        do {

            if (_wcsicmp(moduleEntry.szModule, target_module) == 0) {
                CloseHandle(snapshotHandle);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        } while (Module32NextW(snapshotHandle, &moduleEntry));
    }
    CloseHandle(snapshotHandle);
    return NULL;
}

BOOL Process::IsProcessRunning(DWORD pid_to_check)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid_to_check);
    if (hProcess == NULL) {
        return false; // Process handle couldn't be obtained, possibly not running
    }

    DWORD exitCode;
    if (GetExitCodeProcess(hProcess, &exitCode)) {
        CloseHandle(hProcess);
        return exitCode == STILL_ACTIVE;
    }
    else {
        CloseHandle(hProcess);
        return false; // Could not get exit code, assume process not running
    }
}
