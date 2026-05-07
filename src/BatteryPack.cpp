#include "BatteryPack.h"

BatteryPack::BatteryPack(): index(globalPackIndex++), overVoltage(0), deltaVoltage(0){}

void BatteryPack::determineOverVoltage(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells){
    mV packVoltage = 0;
    for (auto const &cell: batteryCells){
        packVoltage += cell.getVoltage();
    }

    if (packVoltage > PACK_OVER_TOTAL_VOLTAGE){
        this->overVoltage = packVoltage - PACK_OVER_TOTAL_VOLTAGE;
    } else{
        this->overVoltage = 0;
    }
}


void BatteryPack::determineDeltaVoltage(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells){

    std::array<mV, NUM_OF_BATTERY_CELLS> cellVoltages;
    for (int i = 0; i < NUM_OF_BATTERY_CELLS; i++){
        cellVoltages[i] = batteryCells[i].getVoltage();
    }


    mV delta = *std::max_element(begin(cellVoltages), end(cellVoltages)) - *std::min_element(begin(cellVoltages), end(cellVoltages));

    if (delta >= PACK_OVER_DELTA_VOLTAGE){
        this->deltaVoltage = delta - PACK_OVER_DELTA_VOLTAGE;
    }
    else {
        this->deltaVoltage = 0;
    }
}


void BatteryPack::update(std::array<BatteryCell, NUM_OF_BATTERY_CELLS> const &batteryCells){
    determineOverVoltage(batteryCells);
    determineDeltaVoltage(batteryCells);
}


void BatteryPack::packInfo() const{
    std::cout << "######## PACK -" 	<< this->index << "- INFO ########" << std::endl;
    std::cout << "over voltage:\t" 	<< this->overVoltage<< std::endl;
    std::cout << "delta voltage:\t" << this->deltaVoltage<< std::endl << std::endl;
}


mV BatteryPack::getOverVoltage() const{
    return this->overVoltage;
}
mV BatteryPack::getDeltaVoltage() const{
    return this->deltaVoltage;
}


int BatteryPack::globalPackIndex;
