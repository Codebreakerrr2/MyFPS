#include "profiling/LoggerManager.h"
#include "profiling/ConsoleLogger.h"
#include "profiling/UILogger.h"
#include "profiling/FileLogger.h"


namespace Logging{

    LoggerManager::LoggerManager(): consoleLogger(std::make_unique<ConsoleLogger>()),uiLogger(std::make_unique<UILogger>()),
    fileLogger(std::make_unique<FileLogger>("logs/runttimeLogs.log"))  {}
    void LoggerManager::Log(const std::string& msg,LogLevel logerType) {
        
        if(consoleActive){
            consoleLogger->Log(msg,logerType);
        }
        if(uiActive){
            uiLogger->Log(msg,logerType);
        }
        if(logFileActive){
            fileLogger->Log(msg,logerType);
        } 
    }

    void LoggerManager::setConsoleLog(bool active){
        consoleActive = active;
    }
    void LoggerManager::setUILog(bool active){
        uiActive = active;
    }


    void LoggerManager::setFileLog(bool active){
        logFileActive = active;
    }


    





}