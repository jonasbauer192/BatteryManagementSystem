#pragma once

#ifndef BALANCINGCONTROLLER_H_
#define BALANCINGCONTROLLER_H_

#include "BatteryPack.h"
#include "BatteryCell.h"
#include "config.h"
#include <stdint.h>
#include <array>
#include <vector>
#include <numeric>
#include <iostream>
#include <thread>

class BalancingController{
private:
    static int globalCellIndex;
    int index;
    BatteryPack batteryPack;
    std::array<BatteryCell, NUM_OF_BATTERY_CELLS> batteryCells;
    HardwareAccess hw;
    int iteration;

    mV determineDischargeAmount(int const cellIndex) const;
    void report();
    void serviceRoutine();
    void update();

public:
    BalancingController();
    void execute();
};

#endif
