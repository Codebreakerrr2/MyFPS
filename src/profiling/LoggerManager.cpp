#include "profiling/LoggerManager.h"
#include "profiling/ConsoleLogger.h"
#include "profiling/UILogger.h"


namespace Logging{

    LoggerManager::LoggerManager(): consoleLogger(std::make_unique<ConsoleLogger>()),uiLogger(std::make_unique<UILogger>())  {}
    void LoggerManager::Log(const std::string& msg,LogLevel logerType) const{
        if(loggerManagerActive){
        if(consoleActive){
            consoleLogger->Log(msg,logerType);
        }
        if(uiActive){
            uiLogger->Log(msg,logerType);
        } 
    }

    }
    void LoggerManager::setConsoleLog(bool active){
        consoleActive = active;
    }
    void LoggerManager::setUILog(bool active){
        uiActive = active;
    }


        void LoggerManager::setActive(bool active){
            loggerManagerActive= active;
        }


    





}