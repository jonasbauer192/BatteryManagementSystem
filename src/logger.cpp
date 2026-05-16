#include "logger.h"
#include <iostream>
#include <ctime>
#include <sstream>


Logger::Logger(std::string const &filename){
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()){
        std::cout << "ERROR opening log file." << std::endl;
    }
}

Logger::~Logger(){
    logFile.close();
}

std::string Logger::levelToString(LogLevel const level){
    switch (level){
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, std::string const component, std::string const msg){
    time_t timestamp;
    time(&timestamp);

    std::stringstream logEntry;
    logEntry << ctime(&timestamp) << " [" << levelToString(level) << "] [" << component << "]: " << msg << std::endl;

    std::cout << logEntry.str();
    if (logFile.is_open()) {
        logFile << logEntry.str();
        logFile.flush();
    }
}