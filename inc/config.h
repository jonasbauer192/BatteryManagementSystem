#pragma once
#include <stdint.h>

#define NUM_OF_BATTERY_CELLS        4
#define NUM_OF_RAW_MEASUREMENTS     5
#define MAXIMUM_CELL_VOLTAGE        4200
#define MINIMUM_CELL_VOLTAGE        3200
#define CELL_OVER_VOLTAGE           3900
#define CELL_UNDER_VOLTAGE          3300

#define PACK_OVER_TOTAL_VOLTAGE     14000
#define PACK_OVER_DELTA_VOLTAGE     500

#define MAX_MEASUREMENT_ATTEMPTS    3



typedef uint16_t mV;


enum Type{
    LiFePO4 = 1,
    LiIon = 2
};


enum State{
    INIT,
    STANDBY,
    CHARGING,
    DISCHARGING,
    FAULT
};
