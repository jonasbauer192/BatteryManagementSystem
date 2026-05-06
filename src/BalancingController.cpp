#include "BalancingController.h"

BalancingController::BalancingController(): batteryPack(), batteryCells(), iteration(0), hw(){}


mV BalancingController::determineDischargeAmount(int const cellIndex){
    /*
     * finding the charging amount of each cell by identifying the
     * MAXIMUM amount out of cell and pack attributes
     */
    uint16_t numOfActiveCells = 0;
    for (auto &cell: this->batteryCells) {
        if (cell.getState() != FAULT){
            numOfActiveCells++;
        }
    }

    std::array<mV, 3> voltages{
        static_cast<mV>(this->batteryPack.getOverVoltage() / numOfActiveCells),
        static_cast<mV>(this->batteryPack.getDeltaVoltage() / numOfActiveCells),
        this->batteryCells[cellIndex].getOverVoltage()
    };
    return *std::max_element(voltages.begin(), voltages.end());
}


void BalancingController::serviceRoutine(){
    this->iteration++;
    mV amount;
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT) {
            amount = determineDischargeAmount(cell.getIndex());
            if (amount != 0){
                cell.discharge(amount, this->hw);
            }
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
    for (auto &cell: this->batteryCells){
        if (cell.getState() != FAULT) {
            cell.update(this->hw);
        }
    }
    this->batteryPack.update(this->batteryCells);
}


void BalancingController::execute(){
    while(1){
        update();
        serviceRoutine();
        report();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}