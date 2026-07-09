#include "Utils/Logger.h"
#include "Common/Constants.h"

#include <cstdio>
#include <ctime>

static const char* LogLevelToString(LogLevel level)
{
    switch (level)
    {
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Trace:   return "TRACE";
        case LogLevel::Fatal:   return "FATAL";
    }

    return "UNKNOWN";
}

void Logger::Log(LogLevel level, const char* message)
{
        std::time_t now = std::time(nullptr);

        std::tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &now);
#else
        localtime_r(&now, &localTime);
#endif
        char date[DedScope::Constants::DateBufferSize];
        std::strftime(date,
                      sizeof(date),
                      "%Y-%m-%d %H:%M:%S",
                      &localTime);

    printf("[%s] [%s] %s\n",
           date,
           LogLevelToString(level),
           message);
}

void Logger::Info(const char* message)
{
    Log(LogLevel::Info, message);
}

void Logger::Warning(const char* message)
{
    Log(LogLevel::Warning, message);
}

void Logger::Error(const char* message)
{
    Log(LogLevel::Error, message);
}

void Logger::Debug(const char* message)
{
    Log(LogLevel::Debug, message);
}

void Logger::Trace(const char* message)
{
    Log(LogLevel::Trace, message);
}

void Logger::Fatal(const char* message)
{
    Log(LogLevel::Fatal, message);
}