#include "profiling/ConsoleLogger.h"
#include <iostream>
#include <thread>

namespace Logging {

     void ConsoleLogger::Log(const std::string& msg, LogLevel loggerType) {
          std::cout << logLevelToString(loggerType)
                    << "[Thread " << std::this_thread::get_id() << "] "
                    << msg << '\n';
     }

}