#include "ILogger.h"



namespace Logging{


    class ConsoleLogger : public ILogger{

        
         void Log(const std::string& msg,LogLevel loggerType)  override;

};
}