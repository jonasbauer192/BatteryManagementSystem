#include "BatteryCell.h"


#include <vector>
#include <iostream>


BatteryCell::BatteryCell(const Type type, Logger &logger, HardwareAccess &hw):
	hw(hw), index(globalCellIndex++), type(type), state(INIT), overVoltage(0), underVoltage(0), logger(logger) {}


bool BatteryCell::readRawVoltage(mV &rawVoltageSum){
    int attemptCounter;
    for (int i = 0; i < NUM_OF_RAW_MEASUREMENTS; i++){
        attemptCounter = 0;
        while(1){
            attemptCounter++;
            voltage = this->hw.read_cell_voltage_mv(this->index);
            if (voltage){
                rawVoltageSum += voltage;
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
    mV rawVoltageSum = 0;
    if (!readRawVoltage(rawVoltageSum)){
        this->logger.log(ERROR, "Battery Cell", std::to_string(this->index) + ": Read voltage failed.");
        return false;
    }
    this->voltage = (rawVoltageSum /= NUM_OF_RAW_MEASUREMENTS);
    this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": Read voltage succeeded: " + std::to_string(this->voltage));
    return true;
}


void BatteryCell::determineSoc(){
    this->soc = (0.08333 * this->voltage - 250);
    this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": SOC determined: " + std::to_string(this->soc));
}


void BatteryCell::determineOverVoltage(){
    if (this->voltage >= CELL_OVER_VOLTAGE){
        this->overVoltage = this->voltage - CELL_OVER_VOLTAGE;
        this->logger.log(WARNING, "Battery Cell", std::to_string(this->index) + ": Overvoltage: " + std::to_string(this->overVoltage));
    } else{
        this->overVoltage = 0;
        this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": No overvoltage.");
    }
}

void BatteryCell::determineUnderVoltage(){
    if (this->voltage < CELL_UNDER_VOLTAGE){
        this->underVoltage = CELL_UNDER_VOLTAGE - this->voltage;
        this->logger.log(WARNING, "Battery Cell", std::to_string(this->index) + ": Undervoltage: " + std::to_string(this->underVoltage));
    } else{
        this->underVoltage = 0;
        this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": No undervoltage.");
    }
}

void BatteryCell::faultHandling(){
    this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": Fault handling started.");
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
    this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": Discharge started.");
	this->state = DISCHARGING;
	mV targetVoltage = this->voltage - deltaVoltage;

	while(this->voltage > targetVoltage){
	    this->hw.toggle_balancing_resistor(this->index);
	    if (!readVoltage()){
	        return;
	    }
	}
	this->logger.log(INFO, "Battery Cell", std::to_string(this->index) + ": Discharge finished.");
	this->state = STANDBY;
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