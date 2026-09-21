#include "specs/attacks.h"
#include "specs/movement.h"
#include "specs/specs.h"

#include <stdio.h>

#define TABLE_WIDTH 60

static void print_separator(void)
{
    printf("+------------------------------------------------------------+\n");
}

static void print_header(const char *name)
{
    print_separator();
    printf("| %-58s |\n", name);
    print_separator();
}

static void print_row(const char *label, const char *value)
{
    printf("| %-20s | %-35s |\n", label, value);
}

static void print_section_separator(void)
{
    printf("+----------------------+-------------------------------------+\n");
}

const char *monster_type_to_string(monster_type_t type)
{
    switch (type)
    {
        case TYPE_ANIMAL:
            return "Animal";

        case TYPE_PLANT:
            return "Plant";

        case TYPE_ELEMENTAL:
            return "Elemental";

        default:
            return "Unknown";
    }
}

const char *animal_size_to_string(animal_size_t size)
{
    switch (size)
    {
        case SIZE_FINE:
            return "Fine";

        case SIZE_DIMINUTIVE:
            return "Diminutive";

        case SIZE_TINY:
            return "Tiny";

        case SIZE_SMALL:
            return "Small";

        case SIZE_MEDIUM:
            return "Medium";

        case SIZE_LARGE:
            return "Large";

        case SIZE_HUGE:
            return "Huge";

        case SIZE_GARGANTUAN:
            return "Gargantuan";

        case SIZE_COLOSSAL:
            return "Colossal";

        default:
            return "Unknown";
    }
}

const char *movement_geography_to_string(movement_geography_t geography)
{
    switch (geography)
    {
        case MG_NONE:
            return "None";

        case MG_LAND:
            return "Land";

        case MG_FLY_POOR:
            return "Fly (Poor)";

        case MG_FLY_AVERAGE:
            return "Fly (Average)";

        case MG_FLY_GOOD:
            return "Fly (Good)";

        case MG_FLY_PERFECT:
            return "Fly (Perfect)";

        case MG_SWIM:
            return "Swim";

        case MG_BURROW:
            return "Burrow";

        case MG_CLIMB:
            return "Climb";

        default:
            return "Unknown";
    }
}

const char *natural_weapon_type_to_string(natural_weapon_type_t type)
{
    switch (type)
    {
        case NW_NONE:
            return "None";

        case NW_CLAW:
            return "Claw";

        case NW_BITE:
            return "Bite";

        case NW_GORE:
            return "Gore";

        case NW_TENTACLE:
            return "Tentacle";

        case NW_RAKE:
            return "Rake";

        case NW_CONSTRICT:
            return "Constrict";

        case NW_HOOF:
            return "Hoof";

        case NW_RAM:
            return "Ram";

        case NW_REND:
            return "Rend";

        case NW_POWERFULL_CHARGE:
            return "Powerful Charge";

        case NW_TALON:
            return "Talon";

        case NW_SLAM:
            return "Slam";

        case NW_TAIL_SLAP:
            return "Tail Slap";

        case NW_ARMS:
            return "Arms";

        case NW_STAMP:
            return "Stamp";

        case NW_WING:
            return "Wing";

        case NW_BURNING_TOUCH:
            return "Burning Touch";

        default:
            return "Unknown";
    }
}

const char *natural_attack_role_to_string(natural_attack_role_t role)
{
    switch (role)
    {
        case NAR_NONE:
            return "None";

        case NAR_PRIMARY:
            return "Primary";

        case NAR_SECONDARY:
            return "Secondary";

        case NAR_SPECIAL:
            return "Special";

        default:
            return "Unknown";
    }
}

const char *special_attack_type_to_string(special_attack_type_t type)
{
    switch (type)
    {
        case SA_NONE:
            return "None";

        case SA_IMPROVED_GRAB:
            return "Improved Grab";

        case SA_POUNCE:
            return "Pounce";

        case SA_RAKE:
            return "Rake";

        case SA_TRAMPLE:
            return "Trample";

        case SA_TRIP:
            return "Trip";

        case SA_CONSTRICT:
            return "Constrict";

        case SA_POISON:
            return "Poison";

        case SA_REND:
            return "Rend";

        case SA_FEROCITY:
            return "Ferocity";

        case SA_RAGE:
            return "Rage";

        case SA_POWERFUL_CHARGE:
            return "Powerful Charge";

        case SA_ATTACH:
            return "Attach";

        case SA_BLOOD_DRAIN:
            return "Blood Drain";

        case SA_DISEASE:
            return "Disease";

        case SA_SHRIEK:
            return "Shriek";

        case SA_ENTANGLE:
            return "Entangle";

        case SA_PARALYSIS:
            return "Paralysis";

        case SA_SWALLOW_WHOLE:
            return "Swallow Whole";

        case SA_DISTRACTION:
            return "Distraction";

        case SA_WHIRLWIND:
            return "Whirlwind";

        case SA_VORTEX:
            return "Vortex";

        case SA_BURN:
            return "Burn";

        case SA_PUSH:
            return "Push";

        case SA_SMOKE_CLAWS:
            return "Smoke Claws";

        case SA_COMBUSTION:
            return "Combustion";

        case SA_FIERY_AURA:
            return "Fiery Aura";

        case SA_HEAT:
            return "Heat";

        default:
            return "Unknown";
    }
}

void print_animal(const wildshape_form_t *animal)
{
    char buffer[128];

    print_header(animal->name);

    /* Basic properties */

    snprintf(buffer, sizeof(buffer), "%s", animal_size_to_string(animal->size));
    print_row("Size", buffer);

    snprintf(buffer, sizeof(buffer), "%d", animal->armorclass);
    print_row("AC", buffer);

    snprintf(buffer, sizeof(buffer), "%d ft", animal->reach);
    print_row("Reach", buffer);

    snprintf(buffer, sizeof(buffer), "%+d", animal->grapple);
    print_row("Grapple", buffer);

    /* Speeds */

    print_row("Speeds", "");

    for (size_t i = 0; animal->speed[i].geography != MG_NONE && i < MAX_MOVEMENT_TYPE; ++i)
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "%s %d ft",
                 movement_geography_to_string(animal->speed[i].geography),
                 animal->speed[i].range);

        print_row("", buffer);
    }

    /* Ability scores */

    snprintf(buffer,
             sizeof(buffer),
             "STR %d  DEX %d  CON %d",
             animal->ability_scores.strength,
             animal->ability_scores.dexterity,
             animal->ability_scores.constitution);
    print_row("Ability Scores", buffer);

    snprintf(buffer,
             sizeof(buffer),
             "INT %d  WIS %d  CHA %d",
             animal->ability_scores.intelligence,
             animal->ability_scores.wisdom,
             animal->ability_scores.charisma);
    print_row("", buffer);

    /* Saves */

    snprintf(buffer,
             sizeof(buffer),
             "Fort %+d  Ref %+d  Will %+d",
             animal->saves.fortitude,
             animal->saves.reflex,
             animal->saves.will);
    print_row("Saves", buffer);

    print_section_separator();

    /* Natural attacks */

    print_row("Natural Attacks", "");

    for (size_t i = 0; animal->attacks.natural_weapons[i].type != NW_NONE && i < MAX_NATURAL_WEAPONS; ++i)
    {
        const natural_weapon_t *weapon = &animal->attacks.natural_weapons[i];

        snprintf(buffer,
                 sizeof(buffer),
                 "%s %+d(%dd%d%+d) %s",
                 natural_weapon_type_to_string(weapon->type),
                 weapon->attack_bonus,
                 weapon->dice_count,
                 weapon->dice_sides,
                 weapon->damage_bonus,
                 weapon->role == NAR_SPECIAL ? "(SPECIAL)" : "");
        print_row("", buffer);
    }

    /* Full attack */

    print_row("Full Attack", "");

    for (size_t i = 0; animal->attacks.full_attack[i].type != NW_NONE && i < MAX_FULL_ATTACK_ENTRIES; ++i)
    {
        const full_attack_entry_t *entry = &animal->attacks.full_attack[i];

        snprintf(buffer, sizeof(buffer), "%s ×%d", natural_weapon_type_to_string(entry->type), entry->count);

        print_row("", buffer);
    }

    /* Special attacks */

    print_section_separator();

    print_row("Special Attacks", "");

    for (size_t i = 0; animal->attacks.special_attacks[i].type != SA_NONE && i < MAX_SPECIAL_ATTACKS; ++i)
    {
        const int count = animal->attacks.special_attacks[i].count;

        if (count != 1)
        {
            snprintf(buffer,
                     sizeof(buffer),
                     "%s x%d",
                     special_attack_type_to_string(animal->attacks.special_attacks[i].type),
                     count);
        }
        else
        {
            snprintf(
                buffer, sizeof(buffer), "%s", special_attack_type_to_string(animal->attacks.special_attacks[i].type));
        }

        print_row("", buffer);
    }

    print_section_separator();

    print_row("Notes", animal->notes);

    print_separator();
}
