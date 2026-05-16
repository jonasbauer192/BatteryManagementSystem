#include "BalancingController.h"
#include "logger.h"


int main(){

    Logger logger("logFile.txt");

    BalancingController ctrl(2, logger);
    ctrl.run();

    return 0;
}
