#include "BatteryCell.h"
#include "BatteryPack.h"
#include "BalancingController.h"
#include "config.h"

#include <iostream>

int main(){
    BalancingController ctrl;
    ctrl.execute();

    return 0;
}
