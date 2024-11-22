#ifndef OFFSETS_H
#define OFFSETS_H

// Offsets für das Spiel

#define LOCAL_PLAYER 0x0017E0A8  // BASE_ADDRESS + LOCAL_PLAYER

#define AMMO_OFFSET 0x140 // BASE_ADDRESS + AMMO_OFFSET + LOCAL_PLAYER == address of ammo
#define HEALTH 0xEC

#endif // OFFSETS_H
