#pragma once

#ifndef BATTERYPACK_H_
#define BATTERYPACK_H_

#include "config.h"
#include "BatteryCell.h"
#include "logger.h"

#include <stdint.h>
#include <array>
#include <algorithm>
#include <thread>

class BatteryPack{
private:
    mV overVoltage;
    mV deltaVoltage;
    int iteration;

    Logger &logger;

    HardwareAccess hw;
    std::vector<BatteryCell> batteryCells;


    mV determineDischargeAmount(int const cellIndex) const;
    void serviceRoutine();

    void update();

    bool packActive();

    void packInfo() const;
    void determineOverVoltage();
    void determineDeltaVoltage();
public:
    BatteryPack(Logger &logger);
    void execute();


};

#endif
