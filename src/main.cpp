#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>

#include "memory.h"
#include "memory/memory.h"


namespace offsets {
    constexpr auto ammo = 0x168014;   // Offset für Ammo
}

int main() {
    // Verbindung zu ac_client.exe herstellen
    const auto mem = Memory("ac_client.exe");

    std::cout << "ac_client.exe gefunden!" << std::endl;

    // Modulbasisadresse abrufen
    const auto moduleBase = mem.GetModuleAddress("ac_client.exe");
    std::cout << "Module Base -> 0x" << std::hex << moduleBase << std::dec << std::endl;

    while (true) {
        // CPU entlasten
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Ammo-Wert auslesen
        const auto ammoAddress = moduleBase + offsets::ammo;
        const auto currentAmmo = mem.Read<int>(ammoAddress);

        // Ammo-Wert ausgeben
        std::cout << "Ammo: " << currentAmmo << std::endl;
    }

    return 0;
}



