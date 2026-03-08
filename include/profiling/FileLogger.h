#pragma once
#include <string>
#include <fstream>
#include "ILogger.h"

namespace Logging{


class FileLogger : public ILogger{

// eine datei in dem man sachen reinpacken kann mit einer funktion write? write kann man dann beliebig ändenr oder auch die datei art etc. 
public:
    FileLogger(const std::string& filePath);
    ~FileLogger();
    void Log(const std::string& msg,LogLevel logType)  override;

    private:
        std::ofstream file;

};

}