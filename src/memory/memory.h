#ifndef MEMORY_H
#define MEMORY_H

#include <Windows.h>

// Funktion zum Abrufen der Prozess-ID über den Prozessnamen
DWORD GetProcessIdByName(const char* processName);

// Funktion zum Lesen aus dem Speicher
bool ReadMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize);

// Funktion zum Schreiben in den Speicher
bool WriteMemory(HANDLE hProcess, uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize);

#endif // MEMORY_H
