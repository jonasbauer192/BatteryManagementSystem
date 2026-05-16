#include "BatteryCell.h"
#include "BatteryPack.h"
#include "BalancingController.h"
#include "config.h"
#include "logger.h"

#include <iostream>

int main(){

    Logger logger("logFile.txt");

    BalancingController ctrl(2, logger);
    ctrl.run();

    return 0;
}
