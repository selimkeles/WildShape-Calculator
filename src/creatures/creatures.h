#ifndef CREATURES_H
#define CREATURES_H
#include "specs/attacks.h"
#include "specs/movement.h"
#include "specs/specs.h"

typedef struct
{
    char *name;
    animal_size_t size;
    int hd;
    monster_type_t type;
    int strength;
    int dexterity;
    int constitution;
    int armorclass;
    int reach;
    int grapple;
    int fortitude;
    int ref;
    int will;
    speed_t speed[MAX_MOVEMENT_TYPE];
    attacks_t attacks;
} animal_specs_t;

extern const animal_specs_t animals[];
extern const size_t total_creatures;
#endif
