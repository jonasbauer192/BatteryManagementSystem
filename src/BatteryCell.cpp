#include "BatteryCell.h"


BatteryCell::BatteryCell(): BatteryCell(LiIon){}


BatteryCell::BatteryCell(const Type type):
	index(globalCellIndex++), type(type), state(INIT), overVoltage(0), underVoltage(0){}


bool BatteryCell::readRawVoltage(std::vector<mV> &rawVoltages){
    int attemptCounter;
    mV voltage;
    for (int i = 0; i < NUM_OF_RAW_MEASUREMENTS; i++){
        attemptCounter = 0;
        while(1){
            attemptCounter++;
            voltage = read_cell_voltage_mv(this->index);
            if (voltage){
                rawVoltages.push_back(voltage);
                break;
            }

            if (attemptCounter >= MAX_MEASUREMENT_ATTEMPTS){
                faultHandling();
                return false;
            }
        }
    }
    return true;
}


bool BatteryCell::readVoltage(){

    std::vector<mV> rawVoltages;
    if (!readRawVoltage(rawVoltages)){
        return false;
    }


    mV voltage = 0;
    for (auto const i: rawVoltages){
        voltage += i;
    }

    this->voltage = (voltage /= rawVoltages.size());
    return true;
}


void BatteryCell::determineSoc(){
    this->soc = (0.08333 * this->voltage - 250);
}


void BatteryCell::determineOverVoltage(){
    if (this->voltage >= CELL_OVER_VOLTAGE){
        this->overVoltage = this->voltage - CELL_OVER_VOLTAGE;
    } else{
        this->overVoltage = 0;
    }
}


void BatteryCell::determineUnderVoltage(){
    if (this->voltage < CELL_UNDER_VOLTAGE){
        this->underVoltage = CELL_UNDER_VOLTAGE - this->voltage;
    } else{
        this->underVoltage = 0;
    }
}


void BatteryCell::faultHandling(){
    this->state = FAULT;
    this->voltage = 0;
    this->soc = 0;
    this->overVoltage = 0;
    this->underVoltage = 0;
}


void BatteryCell::update(){
    if (!readVoltage()){
        return;
    }
    determineSoc();
    determineOverVoltage();
    determineUnderVoltage();
}


void BatteryCell::discharge(mV const deltaVoltage){
	this->state = DISCHARGING;
	mV targetVoltage = this->voltage - deltaVoltage;

	while(this->voltage > targetVoltage){
	    toggle_balancing_resistor(this->index);
	    if (!readVoltage()){
	        return;
	    }
	}
	this->state = STANDBY;
}


void BatteryCell::cellInfo() const{
    std::cout << "######## CELL -" 	<< this->index << "- INFO ########" << std::endl;
    std::cout << "type:\t\t" 		<< this->type << std::endl;
    std::cout << "state:\t\t" 		<< this->state << std::endl;
    std::cout << "voltage:\t" 		<< this->voltage << std::endl;
    std::cout << "soc:\t\t" 		<< this->soc << std::endl;
    std::cout << "over voltage:\t" 	<< this->overVoltage << std::endl;
    std::cout << "under voltage:\t" << this->underVoltage << std::endl << std::endl;
}


int BatteryCell::getIndex() const{
    return this->index;
}

State BatteryCell::getState() const{
    return this->state;
}


mV BatteryCell::getVoltage() const{
    return this->voltage;
}

mV BatteryCell::getOverVoltage() const{
    return this->overVoltage;
}

mV BatteryCell::getUnderVoltage() const{
    return this->underVoltage;
}

int BatteryCell::globalCellIndex;