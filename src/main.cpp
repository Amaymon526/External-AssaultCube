#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>

#include "memory/memory.h"
#include "offsets/Offsets.h"

using namespace std;

int main() {
    const char* processName = "ac_client.exe";
    const char* moduleName = "ac_client.exe";

    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0) {
        cerr << "Process '" << processName << "' not found!" << endl;
        return -1;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(pid, moduleName);
    if (moduleBase == 0) {
        cerr << "Module '" << moduleName << "' not found!" << endl;
        return -1;
    }

    cout << "Base address of '" << moduleName << "': 0x" << hex << moduleBase << endl;


    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (hProcess == nullptr) {
        cerr << "OpenProcess failed. Error: " << GetLastError() << endl;
        return -1;
    }

    cout << "Successfully connected to process '" << processName << "' (PID: " << pid << ")." << endl;


    uintptr_t baseAddress = moduleBase + LOCAL_PLAYER;

    cout << "baseAddress: 0x" << hex << baseAddress << endl;


    uintptr_t localPlayerAddress = 0;

    if (!ReadMemory(hProcess, baseAddress, &localPlayerAddress, sizeof(uintptr_t))) {
        cerr << "Error reading the local player address." << endl;
        return -1;
    }


    uintptr_t ammoAddress = localPlayerAddress + AMMO_OFFSET;

    int maxAmmo = 20;

    while (true) {
        int ammo = 0;
        
        if (!ReadMemory(hProcess, ammoAddress, &ammo, sizeof(int))) {
            cerr << "Error reading ammo. Error: " << GetLastError() << endl;
            break;
        }

        cout << "Ammo: " << ammo << endl;

        if (ammo < maxAmmo) {
            if (!WriteMemory(hProcess, ammoAddress, &maxAmmo, sizeof(int))) {
                cerr << "Error writing ammo. Error: " << GetLastError() << endl;
                break;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(250));
    }

    CloseHandle(hProcess);
    return 0;
}
