#include "hw_access.h"

// Simulated Analog-to-Digital Converter (ADC) reads
uint16_t read_cell_voltage_mv(int cell_index) {
    bool rnd = std::rand() % 10;
    if (rnd){
        // Should return values between 3000 and 4200 (mV)
        return 3200 + (std::rand() % 1000);
    }
    return 0;
}

float read_pack_current_ma() {
    // Positive for charging, negative for discharging
    return static_cast<float>((std::rand() % 20000) - 10000);
}

void toggle_balancing_resistor(int cell_index) {
    // Hardware command to burn off energy for a specific cell
}
