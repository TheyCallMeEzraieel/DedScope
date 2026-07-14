#pragma once

enum class LogLevel
{

    Info,
    Warning,
    Error,
    Debug,
    Trace,
    Fatal
};

class Logger
{
public:

    static void Log(LogLevel level, const char* message);

    static void Info(const char* message);
    static void Warning(const char* message);
    static void Error(const char* message);
    static void Debug(const char* message);
    static void Trace(const char* message);
    static void Fatal(const char* message);
};