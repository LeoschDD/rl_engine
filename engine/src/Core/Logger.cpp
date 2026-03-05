#include "Core/Logger.hpp"
#include <iostream>

namespace rle
{
    LogLevel Logger::s_min_level_ = LogLevel::Trace;

    const char* Logger::LevelPrefix(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Trace: return "[TRACE]";
            case LogLevel::Info: return "[INFO] ";
            case LogLevel::Warn: return "[WARN] ";
            case LogLevel::Error: return "[ERROR]";
            case LogLevel::Fatal: return "[FATAL]";
        }
        return "[?]";
    }

    const char* Logger::LevelColor(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Trace: return "\033[37m";
            case LogLevel::Info: return "\033[32m";
            case LogLevel::Warn: return "\033[33m";
            case LogLevel::Error: return "\033[31m";
            case LogLevel::Fatal: return "\033[1;31m";
        }
        return "\033[0m";
    }

    void Logger::Log(LogLevel level, const std::string& msg)
    {
        if (level < s_min_level_) return;

        constexpr const char* reset = "\033[0m";
        auto& out = (level >= LogLevel::Error) ? std::cerr : std::cout;
        out << LevelColor(level) << LevelPrefix(level) << reset << " " << msg << "\n";
    }
}
