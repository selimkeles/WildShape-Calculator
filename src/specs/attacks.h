#ifndef ATTACKS_H
#define ATTACKS_H

#include <stddef.h>

#define MAX_FULL_ATTACK_ENTRIES 5
#define MAX_NATURAL_WEAPONS     3
#define MAX_SPECIAL_ATTACKS     3
#define ATTACK_PRESET           -10

typedef enum
{
    // Attack Type
    NW_NONE = 0,
    NW_CLAW,
    NW_BITE,
    NW_GORE,
    NW_TENTACLE,
    NW_RAKE,
    NW_CONSTRICT
} natural_weapon_type_t;

typedef enum
{
    SA_NONE,
    SA_IMPROVED_GRAB,
    SA_POUNCE,
    SA_RAKE,
    SA_TRAMPLE,
    SA_TRIP,
    SA_CONSTRICT,
    SA_POISON,
    // ...
} special_attack_type_t;

typedef enum
{
    NAR_NONE,
    NAR_PRIMARY,
    NAR_SECONDARY,
    NAR_SPECIAL
} natural_attack_role_t;

typedef struct
{
    natural_weapon_type_t type;
    natural_attack_role_t role;

    // int count;
    int attack_bonus;
    int dice_count;
    int dice_sides;
    int damage_bonus;
} natural_weapon_t;

typedef struct
{
    natural_weapon_type_t type;
    int count;
} full_attack_entry_t;

typedef struct
{
    special_attack_type_t type;
    int count;
} special_attack_t;

typedef struct
{
    natural_weapon_t natural_weapons[MAX_NATURAL_WEAPONS];
    full_attack_entry_t full_attack[MAX_FULL_ATTACK_ENTRIES];
    special_attack_t special_attacks[MAX_SPECIAL_ATTACKS];
} attacks_t;

#endif
