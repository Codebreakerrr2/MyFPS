#include "profiling/ConsoleLogger.h"
#include <iostream>

namespace Logging{

void ConsoleLogger::Log(const std::string& msg, LogLevel loggerType) const{
    
switch(loggerType) {
    case LogLevel::ERROR:
        std::cerr << "[ERROR] " << msg << std::endl;
        break;
    case LogLevel::WARNING:
        std::cerr << "[WARNING] " << msg << std::endl;
        break;
    case LogLevel::INFO:
        std::cout << "[INFO] " << msg << std::endl;
        break;
    case LogLevel::DEBUG:
        std::clog << "[DEBUG] " << msg << std::endl;
        break;
    case LogLevel::SUCCESS:
        std::cout << "[SUCCESS] " << msg << std::endl;
        break;
}




}


}





