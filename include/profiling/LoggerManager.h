#pragma once
#include "profiling/ILogger.h"
#include <memory>

namespace Logging{
//this is Singelton so only one instance on the whole project! 
class LoggerManager: public ILogger{


    public:

    static LoggerManager& Get(){
        static LoggerManager loggerManager;
        return loggerManager;
    }
    
    //incase more Logger, make setFunction and bool memeber for it! and check for it in Log function with switch case
    
    void Log(const std::string& msg,LogLevel logerType) const override;
    void setConsoleLog(bool active);
    void setUILog(bool active);
    void setFileLog(bool active);
    void setActive(bool active);
    LoggerManager(const LoggerManager&) =delete;
    LoggerManager& operator=(const LoggerManager&) = delete;


    private:
    //eventuell andere Logger hier RAII Best Practice and no delete needed big brain
    LoggerManager();   
    ~LoggerManager();
    std::unique_ptr<ILogger> consoleLogger;
    std::unique_ptr<ILogger> uiLogger;
    bool consoleActive = true;
    bool uiActive= true;
    bool logFileActive = false;
    bool loggerManagerActive = false;
    };
}