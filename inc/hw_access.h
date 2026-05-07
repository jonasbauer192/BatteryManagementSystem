#ifndef HW_ACCESS_H_
#define HW_ACCESS_H_

#include "config.h"

#include <stdint.h>
#include <random>
#include <array>

class HardwareAccess {
private:
    std::array<uint16_t, NUM_OF_BATTERY_CELLS> voltages;
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> voltage_dist{3200, 4200};
    std::uniform_int_distribution<int> voltage_noice_dist{0, 20};
    std::uniform_int_distribution<int> voltage_reduction_dist{0, 10};
    std::uniform_int_distribution<int> fault_dist{0, 10};

public:
    HardwareAccess();
    uint16_t read_cell_voltage_mv(int cell_index);
    void toggle_balancing_resistor(int cell_index);
};

#endif
