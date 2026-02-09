#pragma once
#include <cstdint>

// Weapon structure (pointer stored at offset 868 in playerent)
struct WeaponStruct
{
    char     unknown0[4];  // 0x00
    int      curweapon;    // 0x04
    char     unknown8[8];  // 0x08
    int* ammo;         // 0x10
    int* magcontent;   // 0x14
};

struct Vec3 { float x, y, z; };

// Player entity structure
struct Player
{
    // Base entity / physics
    char     unknown0[4];  // 0x00 - vtable or other base data
    Vec3     pos;          // 0x04 - 0x0C
    Vec3     vel;          // 0x10 - 0x18
    Vec3     delta;        // 0x1C - 0x24
    Vec3     old_pos;      // 0x28 - 0x30
    float    yaw;          // 0x34
    float    pitch;        // 0x38
    float    roll;         // 0x3C (unused)
    char     unknown64[38]; // 0x40 - 0x65 padding to scoping

    uint8_t  scoping;      // 0x66
    char     unknown103[15]; // 0x67 - 0x75 padding to state
    uint8_t  state;        // 0x76 - alive/dead
    char     unknown119[117]; // 0x77 - 0xEC padding to health

    int      health;       // 0xEC
    int      armour;       // 0xF0
    int      primary;      // 0xF4
    int      nextprimary;  // 0xF8
    char     unknown252[8]; // 0xFC - padding to ping/pj
    int      ping;         // 0x1CC
    int      pj;           // 0x1D0
    char     unknown268[8]; // 0x1D4 - padding to client info
    int      client_info;  // 0x1D8
    int      frags;        // 0x1DC
    int      flags;        // 0x1E0
    int      deaths;       // 0x1E4
    int      teamkills;    // 0x1E8
    char     unknown492[8]; // 0x1EC - padding
    int      role;         // 0x200
    uint8_t  attacking;    // 0x204
    char     name[16];     // 0x205 - adjust length if needed
    int      skin_cla;     // 0x1BC
    int      skin_rvsf;    // 0x1C0
    int      cn;           // 0x1C4
    char     unknown444[316]; // 0x1C8 - 0x30B padding to team
    int      team;         // 0x30C
    char     unknown784[8]; // 0x310 - padding to spect_mode
    int      spect_mode;   // 0x318
    char     unknown792[72]; // 0x31C - padding to weapon_struct
    WeaponStruct* weapon_struct; // 0x364 (868)
};