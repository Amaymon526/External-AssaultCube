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

bool ReadMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    return ReadProcessMemory(hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, nullptr) != 0;
}

bool WriteMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    return WriteProcessMemory(hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, nullptr) != 0;
}
