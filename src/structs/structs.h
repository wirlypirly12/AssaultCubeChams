#pragma once
#include <cstdint>

struct Vec3
{
    float x, y, z;
};

struct WeaponStruct
{
    char     unknown0[4];
    int      curweapon;
    char     unknown8[8];
    int* ammo;
    int* magcontent;
};

struct Player
{
    char     unknown0[4];
    Vec3     pos;
    Vec3     vel;
    Vec3     delta;
    Vec3     old_pos;
    float    yaw;
    float    pitch;
    float    roll;
    char     unknown64[38];

    uint8_t  scoping;
    char     unknown103[15];
    uint8_t  state;
    char     unknown119[117];

    int      health;
    int      armour;
    int      primary;
    int      nextprimary;
    char     unknown252[8];
    int      ping;
    int      pj;
    char     unknown268[8];
    int      client_info;
    int      frags;
    int      flags;
    int      deaths;
    int      teamkills;
    char     unknown492[8];
    int      role;
    uint8_t  attacking;
    char     name[16];
    int      skin_cla;
    int      skin_rvsf;
    int      cn;
    char     unknown444[316];
    int      team;
    char     unknown784[8];
    int      spect_mode;
    char     unknown792[72];
    WeaponStruct* weapon_struct;
};
