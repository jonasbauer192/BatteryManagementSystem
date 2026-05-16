#pragma once

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include "config.h"
#include <sstream>
#include <fstream>
#include <ctime>





class Logger{
private:
    std::ofstream logFile;
    std::string levelToString(LogLevel const level);


public:
    Logger(std::string const &filename);
    ~Logger();

    void log(LogLevel const level, std::string const component, std::string const msg);



};

#endif