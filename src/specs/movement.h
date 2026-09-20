#ifndef MOVEMENT_H
#define MOVEMENT_H

#define MAX_MOVEMENT_TYPE 3

typedef enum
{
    MG_NONE = 0,
    MG_LAND,
    MG_FLY_POOR,
    MG_FLY_AVERAGE,
    MG_FLY_GOOD,
    MG_FLY_PERFECT,
    MG_SWIM,
    MG_BURROW,
    MG_CLIMB
} movement_geography_t;

typedef struct
{
    movement_geography_t geography;
    int range;
} speed_t;

#endif
