#include "profiling/ILogger.h"



namespace Logging{


    class UILogger : public ILogger{
         void Log(const std::string& msg,LogLevel loggerType)  override{}
        

};
}