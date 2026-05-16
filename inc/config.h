#pragma once
#include <stdint.h>

constexpr int NUM_OF_BATTERY_CELLS = 8;
constexpr int NUM_OF_BATTERY_CELLS_PER_PACK = 4;
constexpr int NUM_OF_RAW_MEASUREMENTS = 5;
constexpr int MAXIMUM_CELL_VOLTAGE = 200;
constexpr int MINIMUM_CELL_VOLTAGE = 3200;
constexpr int CELL_OVER_VOLTAGE = 3900;
constexpr int CELL_UNDER_VOLTAGE = 3300;

constexpr int PACK_OVER_TOTAL_VOLTAGE = 14000;
constexpr int PACK_OVER_DELTA_VOLTAGE = 500;

constexpr int MAX_MEASUREMENT_ATTEMPTS = 3;



typedef uint16_t mV;


enum Type{
    LiFePO4 = 1,
    LiIon = 2
};

enum LogLevel{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};


enum State{
    INIT,
    STANDBY,
    CHARGING,
    DISCHARGING,
    FAULT
};
