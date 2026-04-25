#pragma once
#include "ILogger.h"
#include <memory>


//#define ENGINE_DEBUG //comment the line if production Mode


#ifdef ENGINE_DEBUG
#define LOG_ERROR(msg)   Logging::LoggerManager::Get().Log(msg, Logging::LogLevel::ERROR)
#define LOG_WARNING(msg) Logging::LoggerManager::Get().Log(msg, Logging::LogLevel::WARNING)
#define LOG_INFO(msg)    Logging::LoggerManager::Get().Log(msg, Logging::LogLevel::INFO)
#define LOG_DEBUG(msg)   Logging::LoggerManager::Get().Log(msg, Logging::LogLevel::DEBUG)
#define LOG_SUCCESS(msg) Logging::LoggerManager::Get().Log(msg, Logging::LogLevel::SUCCESS)
#else
    #define LOG_ERROR(msg) do{}while(0)
    #define LOG_WARNING(msg) do{}while(0)
    #define LOG_INFO(msg) do{}while(0)
    #define LOG_DEBUG(msg) do{}while(0)
    #define LOG_SUCCESS(msg) do{}while(0)
#endif


namespace Logging{
//this is Singelton so only one instance on the whole project! 
class LoggerManager: public ILogger{


    public:

    static LoggerManager& Get(){
        static LoggerManager loggerManager;
        return loggerManager;
    }
    
    //incase more Logger, make setFunction and bool memeber for it! and check for it in Log function with switch case
    
    void Log(const std::string& msg,LogLevel logerType)  override;
    void setConsoleLog(bool active);
    void setUILog(bool active);
    void setFileLog(bool active);
    
    LoggerManager(const LoggerManager&) =delete;
    LoggerManager& operator=(const LoggerManager&) = delete;


    private:
    //eventuell andere Logger hier RAII Best Practice and no delete needed big brain
    LoggerManager();
    std::unique_ptr<ILogger> consoleLogger;
    std::unique_ptr<ILogger> uiLogger;
    std::unique_ptr<ILogger> fileLogger;
    bool consoleActive = true;
    bool uiActive= true;
    bool logFileActive = false;
    };
}