#pragma once

#ifndef BALANCINGCONTROLLER_H_
#define BALANCINGCONTROLLER_H_

#include "BatteryPack.h"
#include "logger.h"

#include <vector>



class BalancingController{
private:
    std::vector<BatteryPack> batteryPacks;
    Logger &logger;
public:
    BalancingController(int const numOfPacks, Logger &logger);
    void run();
};

#endif
