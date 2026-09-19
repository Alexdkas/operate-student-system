#include "Logger.h"

#include <iostream>

std::ofstream Logger::logFile;

void Logger::log(const std::string &message)
{
    if (!logFile.is_open())
    {
        logFile.open("system.log", std::ios::app);
    }

    if (logFile.is_open())
    {
        logFile << message << '\n';
        logFile.flush();
    }
    else
    {
        std::cerr << message << '\n';
    }
}
