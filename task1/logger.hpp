#pragma once

#include <string>


////////////////////////////////////////////////////////////////////////////////

#define LOG_DEBUG( message ) NLogger::Logger::GetInstance().LogDebug( message )
#define LOG_INFO( message ) NLogger::Logger::GetInstance().LogInfo( message )

////////////////////////////////////////////////////////////////////////////////

namespace NLogger
{

////////////////////////////////////////////////////////////////////////////////

class Logger
{
public:
    enum LogLevel
    {
        Debug = 0, Info, None
    };

public:
    static Logger & GetInstance()
    {
        static Logger instance;
        return instance;
    }
    static void SetLogLevel( LogLevel log_level ) { GetInstance().log_level_ = log_level; }

    void LogDebug( const std::string & message ) const;
    void LogInfo( const std::string & message ) const;

private:
    Logger() {}

    Logger( const Logger & other ) = delete;
    Logger( Logger && other ) = delete;

    Logger & operator=( const Logger & other ) = delete;
    Logger & operator=( Logger && other ) = delete;

    void PrintMessage( const std::string & message ) const;

private:
    LogLevel log_level_ = LogLevel::Info;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace NLogger

////////////////////////////////////////////////////////////////////////////////