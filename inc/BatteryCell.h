#pragma once

#ifndef BATTERCELL_H_
#define BATTERYCELL_H_

#include <stdint.h>
#include <array>
#include <vector>
#include <iostream>

#include "config.h"
#include "hw_access.h"

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

    bool readRawVoltage(std::vector<mV> &rawVoltages);
    bool readVoltage();
    void determineSoc();
    void determineOverVoltage();
    void determineUnderVoltage();

    void faultHandling();
public:
    BatteryCell();
    BatteryCell(const Type type);
    void update();
    void discharge(mV const deltaVoltage);
    void cellInfo() const;

    int getIndex() const;
    State getState() const;
    mV getVoltage() const;
    mV getOverVoltage() const;
    mV getUnderVoltage() const;
};

#endif
