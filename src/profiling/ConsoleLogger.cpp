#include "profiling/ConsoleLogger.h"
#include <iostream>

namespace Logging{

void ConsoleLogger::Log(const std::string& msg, LogLevel loggerType) {
     std::cout << logLevelToString(loggerType) << msg << std::endl;


}


}





