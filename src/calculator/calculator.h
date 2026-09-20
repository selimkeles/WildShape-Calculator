#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "creatures/creatures.h"
#include "specs/specs.h"

typedef struct
{
    int bab;
    int base_fort;
    int base_ref;
    int base_will;
    int extra_fort;
    int extra_ref;
    int extra_will;
    int intelligence;
    int wisdom;
    int charisma;
} hero_stats_t;

wildshape_form_t calc_new_stats(animal_specs_t animal_base);
#endif
