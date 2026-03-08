#include "profiling/FileLogger.h"


namespace Logging{


    FileLogger::FileLogger(const std::string& filePath){
     
        file.open(filePath , std::ios::out | std::ios::app);
    }

    FileLogger::~FileLogger(){
        if(file.is_open()){
        file.close();}
    }
    void FileLogger::Log(const std::string& msg,LogLevel logType) {
    
            if(file.is_open()){
                file << logLevelToString(logType) << msg << std::endl;
            }

    }



}