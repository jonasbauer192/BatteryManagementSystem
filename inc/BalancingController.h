#pragma once

#ifndef BALANCINGCONTROLLER_H_
#define BALANCINGCONTROLLER_H_

#include "BatteryPack.h"
#include "BatteryCell.h"
#include "config.h"
#include "logger.h"
#include <stdint.h>
#include <array>
#include <vector>
#include <numeric>
#include <iostream>
#include <thread>

class BalancingController{
private:
    std::vector<BatteryPack> batteryPacks;
    Logger &logger;
public:
    BalancingController(int const numOfPacks, Logger &logger);
    void run();
};

#endif
