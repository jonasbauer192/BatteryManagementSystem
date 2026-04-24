#pragma once

#ifndef BATTERYPACK_H_
#define BATTERYPACK_H_

#include "config.h"
#include "BatteryCell.h"

#include <stdint.h>
#include <array>
#include <algorithm>

class BatteryPack{
private:
    static int globalPackIndex;
    int index;
    mV overVoltage;
    mV deltaVoltage;
    void determineOverVoltage(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells);
    void determineDeltaVoltage(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells);
public:
    BatteryPack();
    void update(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells);
    void packInfo() const;
    mV getOverVoltage() const;
    mV getDeltaVoltage() const;

};

#endif
