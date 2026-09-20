#include "calculator.h"

#include "creatures/creatures.h"
#include "creatures/druid.h"
#include "specs/specs.h"

#include <stddef.h>

//                            FINE  DIMINUTIVE  TINY    SMALL   MEDIUM  LARGE   HUGE    GARGANTUAN  COLOSSAL
const int attack_mod_size[] = {8, 4, 2, 1, 0, -1, -2, -4, -8};
const int grapple_mod_size[] = {-16, -12, -8, -4, 0, 4, 8, 12, 16};

// Druid level change
const int druid_bab[] = {0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15};
const int druid_fort[] = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 15};
const int druid_ref[] = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6};
const int druid_will[] = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 15};

hero_stats_t hero = {druid_bab[HERO_DRUID_LV],
                     druid_fort[HERO_DRUID_LV],
                     druid_ref[HERO_DRUID_LV],
                     druid_will[HERO_DRUID_LV],
                     5,
                     5,
                     5,
                     14,
                     20,
                     14};

static void calculate_ability_modifiers(ability_scores_t *input, ability_modifier_t *output)
{
    output->str_mod = (input->strength - 10) / 2;
    output->con_mod = (input->constitution - 10) / 2;
    output->dex_mod = (input->dexterity - 10) / 2;
    output->int_mod = (input->intelligence - 10) / 2;
    output->wis_mod = (input->wisdom - 10) / 2;
    output->cha_mod = (input->charisma - 10) / 2;
}

static void copy_const_stats(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    ws_form->name = animal->name;
    ws_form->init = ws_form->ability_modifiers.dex_mod;
    ws_form->bab = hero.bab;
    ws_form->size = animal->size;
    ws_form->armorclass = animal->armorclass;
    ws_form->reach = animal->reach;
    ws_form->notes = animal->notes;
}

static void copy_ability_stats(animal_specs_t *animal, ability_scores_t *new_stats)
{
    new_stats->strength = animal->strength;
    new_stats->dexterity = animal->dexterity;
    new_stats->constitution = animal->constitution;
    new_stats->intelligence = hero.intelligence;
    new_stats->wisdom = hero.wisdom;
    new_stats->charisma = hero.charisma;
}

static void calculate_grapple(wildshape_form_t *ws_form)
{
    ws_form->grapple = ws_form->bab + ws_form->ability_modifiers.str_mod + grapple_mod_size[ws_form->size];
}

static void calculate_saves(wildshape_form_t *ws_form)
{
    ws_form->saves.fortitude = hero.base_fort + hero.extra_fort + ws_form->ability_modifiers.con_mod;
    ws_form->saves.reflex = hero.base_ref + hero.extra_ref + ws_form->ability_modifiers.dex_mod;
    ws_form->saves.will = hero.base_will + hero.extra_will + ws_form->ability_modifiers.wis_mod;
}

static void copy_movement_stats(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    int i = 0;
    do
    {
        ws_form->speed[i].geography = animal->speed[i].geography;
        ws_form->speed[i].range = animal->speed[i].range;
        i++;
    } while (animal->speed[i].geography != MG_NONE && i < MAX_MOVEMENT_TYPE);
}

static void calculate_natural_attacks(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    attacks_t *ab_attacks = &animal->attacks;
    attacks_t *ws_attacks = &ws_form->attacks;
    int str_mod = ws_form->ability_modifiers.str_mod;
    int i = 0;
    do
    {
        if (ab_attacks->natural_weapons[i].attack_bonus != ATTACK_PRESET)
        {
            ws_attacks->natural_weapons[i].attack_bonus =
                ws_form->bab + str_mod + attack_mod_size[ws_form->size] +
                (ab_attacks->natural_weapons[i].role == NAR_SECONDARY ? -5 : 0);
            ws_attacks->natural_weapons[i].damage_bonus =
                ab_attacks->natural_weapons[i].role == NAR_SECONDARY ? (str_mod / 2) : str_mod;
        }
        else
        {
            ws_attacks->natural_weapons[i].attack_bonus = 0;
            ws_attacks->natural_weapons[i].damage_bonus = ab_attacks->natural_weapons[i].damage_bonus;
        }

        ws_attacks->natural_weapons[i].dice_count = ab_attacks->natural_weapons[i].dice_count;
        ws_attacks->natural_weapons[i].dice_sides = ab_attacks->natural_weapons[i].dice_sides;
        ws_attacks->natural_weapons[i].role = ab_attacks->natural_weapons[i].role;
        ws_attacks->natural_weapons[i].type = ab_attacks->natural_weapons[i].type;

        i++;
    } while (ab_attacks->natural_weapons[i].type != NW_NONE && i < MAX_NATURAL_WEAPONS);
}

static void calculate_full_attacks(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    calculate_natural_attacks(animal, ws_form);
    attacks_t *ab_attacks = &animal->attacks;
    attacks_t *ws_attacks = &ws_form->attacks;
    int i = 0;
    do
    {
        ws_attacks->full_attack[i].type = ab_attacks->full_attack[i].type;
        ws_attacks->full_attack[i].count = ab_attacks->full_attack[i].count;
        i++;
    } while (ab_attacks->full_attack[i].type != NW_NONE && i < MAX_FULL_ATTACK_ENTRIES);
}

static void calculate_special_attacks(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    calculate_natural_attacks(animal, ws_form);
    attacks_t *ab_attacks = &animal->attacks;
    attacks_t *ws_attacks = &ws_form->attacks;
    int i = 0;
    do
    {
        ws_attacks->special_attacks[i].type = ab_attacks->special_attacks[i].type;
        ws_attacks->special_attacks[i].count = ab_attacks->special_attacks[i].count;
        i++;
    } while (ab_attacks->special_attacks[i].type != SA_NONE && i < MAX_SPECIAL_ATTACKS);
}

static void calculate_attacks(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    calculate_natural_attacks(animal, ws_form);
    calculate_full_attacks(animal, ws_form);
    calculate_special_attacks(animal, ws_form);
}

static void calculate_ws_allowance(animal_specs_t *animal, wildshape_form_t *ws_form)
{
    ws_form->allowed = false;
    if (animal->hd > HERO_DRUID_LV)
    {
        return;
    }
    else if (HERO_DRUID_LV < 12 && animal->type > TYPE_ANIMAL)
    {
        return;
    }
    else if (HERO_DRUID_LV < 16 && animal->type > TYPE_PLANT)
    {
        return;
    }
    else if (HERO_DRUID_LV < 9 && (animal->size < SIZE_SMALL || animal->size > SIZE_MEDIUM))
    {
        return;
    }
    else if (HERO_DRUID_LV < 11 && (animal->size < SIZE_SMALL || animal->size > SIZE_LARGE))
    {
        return;
    }
    else if (HERO_DRUID_LV < 15 && (animal->size < SIZE_TINY || animal->size > SIZE_LARGE))
    {
        return;
    }
    else if (animal->size < SIZE_TINY || animal->size > SIZE_HUGE)
    {
        return;
    }
    else
    {
        ws_form->allowed = true;
        return;
    }
}

wildshape_form_t calc_new_stats(animal_specs_t animal_base)
{
    wildshape_form_t ws_form = {0};
    copy_ability_stats(&animal_base, &ws_form.ability_scores);
    copy_const_stats(&animal_base, &ws_form);
    calculate_ability_modifiers(&ws_form.ability_scores, &ws_form.ability_modifiers);
    calculate_grapple(&ws_form);
    calculate_saves(&ws_form);
    copy_movement_stats(&animal_base, &ws_form);
    calculate_attacks(&animal_base, &ws_form);
    calculate_ws_allowance(&animal_base, &ws_form);
    return ws_form;
}
