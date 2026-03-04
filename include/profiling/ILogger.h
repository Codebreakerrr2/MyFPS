#pragma once
#include <string>

/**
ERROR	Kritische Fehler, die das Programm eventuell abbrechen lassen könnten
WARNING	Probleme, die nicht kritisch sind, aber beachtet werden sollten
INFO	Allgemeine Statusmeldungen, z. B. „Asset geladen“
DEBUG	Detaillierte Debug-Infos für Entwickler, z. B. Variable-Werte
TRACE	Sehr feingranulare Infos, oft pro Funktion / Schritt
FATAL	Extreme Fehler, die sofort Programm beenden
SUCCESS / OK	Optional, um positive Events zu loggen 
 */
namespace Logging{
    
    enum class LogLevel{
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        SUCCESS

    };


class ILogger{


    public:
    virtual ~ILogger()= default;

    virtual void Log(const std::string& msg,LogLevel loggerType) const =0;

};

}