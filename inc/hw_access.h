#ifndef HW_ACCESS_H_
#define HW_ACCESS_H_

#include <stdint.h>
#include <cstdlib>


// Simulated Analog-to-Digital Converter (ADC) reads
uint16_t read_cell_voltage_mv(int cell_index);
float read_pack_current_ma();
void toggle_balancing_resistor(int cell_index);

#endif
