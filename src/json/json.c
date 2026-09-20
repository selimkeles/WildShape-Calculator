#include "json.h"

#include "calculator/calculator.h"
#include "creatures/creatures.h"
#include "table/table.h"

#include "json/mjson/src/mjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int file_printer(const char *buf, int len, void *fnd)
{
    return (int)fwrite(buf, 1, (size_t)len, (FILE *)fnd);
}

static int print_speeds(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const wildshape_form_t *a = va_arg(*ap, const wildshape_form_t *);
    int n = 0;
    for (int i = 0; i < MAX_MOVEMENT_TYPE && a->speed[i].geography != MG_NONE; i++)
    {
        n += mjson_printf(fn,
                          fnd,
                          "%s{%Q:%Q,%Q:%d}",
                          i ? "," : "",
                          "geography",
                          movement_geography_to_string(a->speed[i].geography),
                          "range",
                          a->speed[i].range);
    }
    return n;
}

static int print_ability_scores(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const ability_scores_t *s = va_arg(*ap, const ability_scores_t *);
    return mjson_printf(fn,
                        fnd,
                        "{%Q:%d,%Q:%d,%Q:%d,%Q:%d,%Q:%d,%Q:%d}",
                        "strength",
                        s->strength,
                        "dexterity",
                        s->dexterity,
                        "constitution",
                        s->constitution,
                        "intelligence",
                        s->intelligence,
                        "wisdom",
                        s->wisdom,
                        "charisma",
                        s->charisma);
}

static int print_saves(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const saves_t *s = va_arg(*ap, const saves_t *);
    return mjson_printf(
        fn, fnd, "{%Q:%d,%Q:%d,%Q:%d}", "fortitude", s->fortitude, "reflex", s->reflex, "will", s->will);
}

static int print_natural_weapons(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const attacks_t *attacks = va_arg(*ap, const attacks_t *);
    int n = 0;
    for (int i = 0; i < MAX_NATURAL_WEAPONS && attacks->natural_weapons[i].type != NW_NONE; i++)
    {
        const natural_weapon_t *w = &attacks->natural_weapons[i];
        n += mjson_printf(fn,
                          fnd,
                          "%s{%Q:%Q,%Q:%Q,%Q:%d,%Q:%d,%Q:%d,%Q:%d}",
                          i ? "," : "",
                          "type",
                          natural_weapon_type_to_string(w->type),
                          "role",
                          natural_attack_role_to_string(w->role),
                          "attack_bonus",
                          w->attack_bonus,
                          "dice_count",
                          w->dice_count,
                          "dice_sides",
                          w->dice_sides,
                          "damage_bonus",
                          w->damage_bonus);
    }
    return n;
}

static int print_full_attack(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const attacks_t *attacks = va_arg(*ap, const attacks_t *);
    int n = 0;
    for (int i = 0; i < MAX_FULL_ATTACK_ENTRIES && attacks->full_attack[i].type != NW_NONE; i++)
    {
        const full_attack_entry_t *f = &attacks->full_attack[i];
        n += mjson_printf(fn,
                          fnd,
                          "%s{%Q:%Q,%Q:%d}",
                          i ? "," : "",
                          "type",
                          natural_weapon_type_to_string(f->type),
                          "count",
                          f->count);
    }
    return n;
}

static int print_special_attacks(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const attacks_t *attacks = va_arg(*ap, const attacks_t *);
    int n = 0;
    for (int i = 0; i < MAX_SPECIAL_ATTACKS && attacks->special_attacks[i].type != SA_NONE; i++)
    {
        const special_attack_t *s = &attacks->special_attacks[i];
        n += mjson_printf(fn,
                          fnd,
                          "%s{%Q:%Q,%Q:%d}",
                          i ? "," : "",
                          "type",
                          special_attack_type_to_string(s->type),
                          "count",
                          s->count);
    }
    return n;
}

static int print_attacks(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const attacks_t *attacks = va_arg(*ap, const attacks_t *);
    return mjson_printf(fn,
                        fnd,
                        "{%Q:[%M],%Q:[%M],%Q:[%M]}",
                        "natural_weapons",
                        print_natural_weapons,
                        attacks,
                        "full_attack",
                        print_full_attack,
                        attacks,
                        "special_attacks",
                        print_special_attacks,
                        attacks);
}

static int print_animal_obj(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    const wildshape_form_t *a = va_arg(*ap, const wildshape_form_t *);
    const animal_specs_t *raw = va_arg(*ap, const animal_specs_t *);
    int n = 0;

    n += mjson_printf(fn, fnd, "%Q:%Q,", "name", a->name);
    n += mjson_printf(fn, fnd, "%Q:%Q,", "size", animal_size_to_string(a->size));
    n += mjson_printf(fn, fnd, "%Q:%B,", "allowed", a->allowed);
    n += mjson_printf(fn, fnd, "%Q:%Q,", "notes", a->notes ? a->notes : "");
    n += mjson_printf(fn, fnd, "%Q:%d,", "hd", raw->hd);
    n += mjson_printf(fn, fnd, "%Q:%Q,", "type", monster_type_to_string(raw->type));
    n += mjson_printf(fn, fnd, "%Q:%d,", "init", a->init);
    n += mjson_printf(fn, fnd, "%Q:%d,", "bab", a->bab);
    n += mjson_printf(fn, fnd, "%Q:%d,", "armorclass", a->armorclass);
    n += mjson_printf(fn, fnd, "%Q:%d,", "reach", a->reach);
    n += mjson_printf(fn, fnd, "%Q:%d,", "grapple", a->grapple);
    n += mjson_printf(fn, fnd, "%Q:%M,", "ability_scores", print_ability_scores, &a->ability_scores);
    n += mjson_printf(fn, fnd, "%Q:%M,", "saves", print_saves, &a->saves);
    n += mjson_printf(fn, fnd, "%Q:[%M],", "speeds", print_speeds, a);
    n += mjson_printf(fn, fnd, "%Q:%M", "attacks", print_attacks, &a->attacks);
    return n;
}

static int print_animals(mjson_print_fn_t fn, void *fnd, va_list *ap)
{
    (void)ap;
    int n = 0;
    n += mjson_printf(fn, fnd, "[");
    for (size_t i = 0; i < total_creatures; i++)
    {
        wildshape_form_t form = calc_new_stats(animals[i]);
        n += mjson_printf(fn, fnd, "%s{%M}", i ? "," : "", print_animal_obj, &form, &animals[i]);
    }
    n += mjson_printf(fn, fnd, "]");
    return n;
}

int json_export_animals(const char *path)
{
    FILE *fp;
    char *buf;
    int ok;

    if (path == NULL)
    {
        return -1;
    }

    fp = fopen(path, "w");
    if (fp == NULL)
    {
        return -1;
    }

    buf = mjson_aprintf("{%Q:%M}", "animals", print_animals);
    if (buf == NULL)
    {
        fclose(fp);
        return -1;
    }

    ok = mjson_pretty(buf, (int)strlen(buf), "  ", file_printer, fp);
    fputc('\n', fp);
    fclose(fp);
    free(buf);

    return ok < 0 ? -1 : 0;
}
