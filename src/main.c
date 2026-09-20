#include "calculator/calculator.h"
#include "creatures/creatures.h"
#include "specs/specs.h"
#include "table/table.h"

#include "json/json.h"
#include <stdio.h>

int main(void)
{
    for (size_t i = 0; i < total_creatures; i++)
    {
        wildshape_form_t animal = calc_new_stats(animals[i]);
        print_animal(&animal);
    }

    if (json_export_animals("wildshape.json") != 0)
    {
        fprintf(stderr, "Failed to write wildshape.json\n");
        return 1;
    }
    return 0;
}
