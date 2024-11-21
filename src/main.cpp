#include <Windows.h>
#include <iostream>
#include <thread>
#include "memory.h"
#include "memory/memory.h"
#include "offsets/Offsets.h"

using namespace std;

int main() {
    const char* processName = "ac_client.exe";

    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0) {
        cerr << "Prozess '" << processName << "' nicht gefunden!" << endl;
        return -1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (hProcess == nullptr) {
        cerr << "OpenProcess fehlgeschlagen. Fehler: " << GetLastError() << endl;
        return -1;
    }

    cout << "Erfolgreich mit Prozess '" << processName << "' verbunden (PID: " << pid << ")." << endl;

    uintptr_t moduleBase = 0x400000;

    uintptr_t ammoAddress = AMMO_OFFSET;
    uintptr_t hpAddress = moduleBase + HP_OFFSET;

    int maxAmmo = 20;

    while (true) {
        int ammo = 0, hp = 0;

        if (!ReadMemory(hProcess, ammoAddress, &ammo, sizeof(int))) {
            cerr << "Fehler beim Lesen der Munition. Fehler: " << GetLastError() << endl;
        }
        if (!ReadMemory(hProcess, hpAddress, &hp, sizeof(int))) {
            cerr << "Fehler beim Lesen der HP. Fehler: " << GetLastError() << endl;
        }

        cout << "Ammo: " << ammo << " | HP: " << hp << endl;

        if (ammo < maxAmmo) {
            if (!WriteMemory(hProcess, ammoAddress, &maxAmmo, sizeof(int))) {
                cerr << "Fehler beim Schreiben der Munition. Fehler: " << GetLastError() << endl;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(250));
    }
    CloseHandle(hProcess);
    return 0;
}
