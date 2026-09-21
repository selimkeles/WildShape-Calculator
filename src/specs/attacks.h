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
    NW_HOOF,
    NW_RAM,
    NW_RAKE,
    NW_CONSTRICT,
    NW_REND,
    NW_POWERFULL_CHARGE,
    NW_TALON,
    NW_SLAM,
    NW_TAIL_SLAP,
    NW_ARMS,
    NW_STAMP,
    NW_WING,
    NW_BURNING_TOUCH
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
    SA_REND,
    SA_FEROCITY,
    SA_RAGE,
    SA_POWERFUL_CHARGE,
    SA_ATTACH,
    SA_BLOOD_DRAIN,
    SA_DISEASE,
    SA_SHRIEK,
    SA_ENTANGLE,
    SA_PARALYSIS,
    SA_SWALLOW_WHOLE,
    SA_DISTRACTION,
    SA_WHIRLWIND,
    SA_VORTEX,
    SA_BURN,
    SA_PUSH,
    SA_SMOKE_CLAWS,
    SA_COMBUSTION,
    SA_FIERY_AURA,
    SA_HEAT
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
