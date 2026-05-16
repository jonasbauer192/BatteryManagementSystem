#pragma once

#ifndef BATTERCELL_H_
#define BATTERYCELL_H_

#include <stdint.h>
#include <array>
#include <vector>
#include <iostream>

#include "config.h"
#include "hw_access.h"
#include "logger.h"

class BatteryCell{
private:
    static int globalCellIndex;
    int index;
    Type type;
    State state;
    mV voltage;
    float soc;
    mV overVoltage;
    mV underVoltage;
    HardwareAccess &hw;

    Logger &logger;



    bool readRawVoltage(mV &rawVoltageSum);
    bool readVoltage();
    void determineSoc();
    void determineOverVoltage();
    void determineUnderVoltage();

    void faultHandling();
public:
    BatteryCell(const Type type, Logger &logger, HardwareAccess &hw);
    void update();
    void discharge(mV const deltaVoltage);

    int getIndex() const;
    State getState() const;
    mV getVoltage() const;
    mV getOverVoltage() const;
    mV getUnderVoltage() const;
};

#endif
