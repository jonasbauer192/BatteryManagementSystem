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
    std::vector<BatteryCell*> activeCells;
    HardwareAccess hw;
    int iteration;

    mV determineDischargeAmount(int const cellIndex);
    void report();
    void serviceRoutine();
    void update();
    void findActiveCells();
    void initialize();

public:
    BalancingController();
    void execute();
};

#endif
