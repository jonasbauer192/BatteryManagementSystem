#include "BalancingController.h"
#include "logger.h"

BalancingController::BalancingController(int const numOfPacks, Logger &logger): logger(logger){
    batteryPacks.reserve(numOfPacks);
    for (int i = 0; i < numOfPacks; i++){
        this->logger.log(INFO, "BatteryPack", "Initializing battery pack");
        batteryPacks.emplace_back(logger);
    }
}


void BalancingController::run() {
    for (auto &pack: this->batteryPacks) {
        pack.execute();
    }
}


