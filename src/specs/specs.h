#ifndef SPECS_H
#define SPECS_H

#include "attacks.h"
#include "movement.h"

typedef enum
{
    TYPE_ANIMAL,
    TYPE_PLANT,
    TYPE_ELEMENTAL
} monster_type_t;

typedef enum
{
    SIZE_FINE,
    SIZE_DIMINUTIVE,
    SIZE_TINY,
    SIZE_SMALL,
    SIZE_MEDIUM,
    SIZE_LARGE,
    SIZE_HUGE,
    SIZE_GARGANTUAN,
    SIZE_COLOSSAL
} animal_size_t;

typedef struct
{
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
} ability_scores_t;

typedef struct
{
    int str_mod;
    int dex_mod;
    int con_mod;
    int int_mod;
    int wis_mod;
    int cha_mod;
} ability_modifier_t;

typedef struct
{
    int fortitude;
    int reflex;
    int will;
} saves_t;

typedef struct
{
    char *name;
    int init;
    int bab;
    animal_size_t size;
    ability_scores_t ability_scores;
    ability_modifier_t ability_modifiers;
    saves_t saves;
    int armorclass;
    int reach;
    int grapple;
    speed_t speed[MAX_MOVEMENT_TYPE];
    attacks_t attacks;
} wildshape_form_t;

#endif
