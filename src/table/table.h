#ifndef TABLE_H
#define TABLE_H
#include "specs/specs.h"

void print_animal(const wildshape_form_t *animal);

const char *animal_size_to_string(animal_size_t size);
const char *movement_geography_to_string(movement_geography_t geography);
const char *natural_weapon_type_to_string(natural_weapon_type_t type);
const char *natural_attack_role_to_string(natural_attack_role_t role);
const char *special_attack_type_to_string(special_attack_type_t type);
const char *monster_type_to_string(monster_type_t type);
#endif
