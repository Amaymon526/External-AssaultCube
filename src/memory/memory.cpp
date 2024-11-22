#include "memory.h"
#include <tlhelp32.h>
#include <iostream>

DWORD GetProcessIdByName(const char* processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
    if (Process32First(hSnapshot, &processEntry)) {
        do {
            if (!_stricmp(processEntry.szExeFile, processName)) {
                CloseHandle(hSnapshot);
                return processEntry.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &processEntry));
    }

    CloseHandle(hSnapshot);
    return 0;
}

ptrdiff_t GetModuleBaseAddress(DWORD pid, const char *moduleName) {
    ptrdiff_t  moduleBase = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &me)) {
        do {
            if (_stricmp(me.szModule, moduleName) == 0) {
                moduleBase = (ptrdiff_t )me.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &me));
    }

    CloseHandle(hSnapshot);
    return moduleBase;
}

bool ReadMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    return ReadProcessMemory(hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, nullptr) != 0;
}

bool WriteMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    return WriteProcessMemory(hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, nullptr) != 0;
}
