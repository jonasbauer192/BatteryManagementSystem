#include "BalancingController.h"

BalancingController::BalancingController(): batteryPack(), batteryCells(), iteration(0){}


mV BalancingController::determineDischargeAmount(int const cellIndex){
    /*
     * finding the charging amount of each cell by identifying the
     * MAXIMUM amount out of cell and pack attributes
     */
    std::array<mV, 3> voltages{
        this->batteryPack.getOverVoltage() / static_cast<uint16_t>(this->activeCells.size()),
        this->batteryPack.getDeltaVoltage() / static_cast<uint16_t>(this->activeCells.size()),
        this->batteryCells[cellIndex].getOverVoltage()
    };
    return *std::max_element(voltages.begin(), voltages.end());
}


void BalancingController::serviceRoutine(){
    this->iteration++;
    mV amount;
    for (auto &cell: this->activeCells){
        amount = determineDischargeAmount(cell->getIndex());
        if (amount != 0){
            cell->discharge(amount);
        }
    }
}


void BalancingController::report(){
    std::cout << "///// SERVICE ROUTINE -" << this->iteration << "- /////" << std::endl << std::endl;
    this->batteryPack.packInfo();
    for (auto const &cell: this->batteryCells){
        cell.cellInfo();
    }
    std::cout << "////////////////////////////////" << std::endl << std::endl;
}


void BalancingController::update(){
    for (auto &cell: this->activeCells){
        cell->update();
    }
    this->batteryPack.update(this->batteryCells);
}


void BalancingController::findActiveCells(){
    for (auto iterator = this->activeCells.begin(); iterator < (this->activeCells).end(); ){
        if ((*iterator)->getState() == FAULT){
            iterator = (this->activeCells).erase(iterator);
        } else {
            iterator++;
        }
    }
}


void BalancingController::initialize(){
    for (auto &cell: this->batteryCells){
        this->activeCells.push_back(&cell);
    }
    update();
}


void BalancingController::execute(){
    initialize();

    while(this->activeCells.size() != 0){
        serviceRoutine();
        report();
        std::this_thread::sleep_for(std::chrono::seconds(5));

        update();
        findActiveCells();
    }
}