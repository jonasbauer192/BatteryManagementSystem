#include "hw_access.h"



HardwareAccess::HardwareAccess() {
    for (int i = 0; i < NUM_OF_BATTERY_CELLS; i++) {
        if (fault_dist(rng)) {
            this->voltages[i] = voltage_dist(rng);
        } else {
            this->voltages[i] = 0;
        }
    }
}

uint16_t HardwareAccess::read_cell_voltage_mv(int cell_index) {
    return this->voltages[cell_index] + voltage_noice_dist(rng);
}

void HardwareAccess::toggle_balancing_resistor(int cell_index) {
    this->voltages[cell_index] -= voltage_reduction_dist(rng);
}