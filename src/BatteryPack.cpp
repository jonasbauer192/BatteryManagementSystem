#include "BatteryPack.h"

#include <stdint.h>
#include <array>
#include <algorithm>
#include <thread>

BatteryPack::BatteryPack(Logger &logger)
    : overVoltage(0), deltaVoltage(0), iteration(0), logger(logger), hw(){
        batteryCells.reserve(NUM_OF_BATTERY_CELLS_PER_PACK);
        for (int i = 0; i < NUM_OF_BATTERY_CELLS_PER_PACK; i++){
            batteryCells.emplace_back(LiIon, logger, hw);
        }

    }


mV BatteryPack::determineDischargeAmount(int const cellIndex) const{
    /*
     * finding the charging amount of each cell by identifying the
     * MAXIMUM amount out of cell and pack attributes
     */
    uint16_t numOfActiveCells = 0;
    for (auto const &cell: this->batteryCells) {
        if (cell.getState() != FAULT){
            numOfActiveCells++;
        }
    }

    std::array<mV, 3> voltages{
        static_cast<mV>(this->overVoltage / numOfActiveCells),
        static_cast<mV>(this->deltaVoltage / numOfActiveCells),
        this->batteryCells[cellIndex].getOverVoltage()
    };
    return *std::max_element(voltages.begin(), voltages.end());
}

void BatteryPack::serviceRoutine(){
    this->logger.log(INFO, "Battery Pack", "---------------- Service routine started ----------------");
    this->iteration++;
    mV amount;
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT) {
            amount = determineDischargeAmount(cell.getIndex() % NUM_OF_BATTERY_CELLS_PER_PACK);
            if (amount != 0){
                cell.discharge(amount);
            }
        }
    }
}



void BatteryPack::update(){
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT) {
            cell.update();
        }
    }
    determineOverVoltage();
    determineDeltaVoltage();
}

bool BatteryPack::packActive(){
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT){
            return true;
        }
    }
    return false;
}


void BatteryPack::execute(){
    while(packActive()){
        update();
        serviceRoutine();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void BatteryPack::determineOverVoltage(){
    mV packVoltage = 0;
    for (auto const &cell: batteryCells){
        packVoltage += cell.getVoltage();
    }

    if (packVoltage > PACK_OVER_TOTAL_VOLTAGE){
        this->overVoltage = packVoltage - PACK_OVER_TOTAL_VOLTAGE;
        this->logger.log(WARNING, "Battery Pack", "Overvoltage.");
    } else{
        this->overVoltage = 0;
        this->logger.log(INFO, "Battery Pack", "No overvoltage.");
    }
}

void BatteryPack::determineDeltaVoltage(){
    std::vector<mV> cellVoltages;
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT) {
                cellVoltages.push_back(cell.getVoltage());
        }
    }

    mV delta = *std::max_element(begin(cellVoltages), end(cellVoltages)) - *std::min_element(begin(cellVoltages), end(cellVoltages));

    if (delta >= PACK_OVER_DELTA_VOLTAGE){
        this->deltaVoltage = delta - PACK_OVER_DELTA_VOLTAGE;
        this->logger.log(WARNING, "Battery Pack", "Delta voltage exceeded.");
    }
    else {
        this->deltaVoltage = 0;
        this->logger.log(INFO, "Battery Pack", "Delta voltage not exceeded.");
    }
}
