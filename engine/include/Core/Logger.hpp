#pragma once

#include <format>
#include <string>

namespace rle
{
    enum class LogLevel { Trace, Info, Warn, Error, Fatal };

    class Logger
    {
    public:
        template<typename... Args>
        static void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
        {
            Log(level, std::format(fmt, std::forward<Args>(args)...));
        }
        
        template<typename... Args>
        static void LogAt(LogLevel level, const char* file, int line, std::format_string<Args...> fmt, Args&&... args)
        {
            Log(level, std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...)));
        }

        static void Log(LogLevel level, const std::string& msg);

        static void SetMinLevel(LogLevel level) { s_min_level_ = level; }

    private:
        static LogLevel s_min_level_;

        static const char* LevelPrefix(LogLevel level);
        static const char* LevelColor(LogLevel level);
    };
}

#define RLE_LOG_TRACE(fmt, ...) rle::Logger::Log(rle::LogLevel::Trace, fmt __VA_OPT__(,) __VA_ARGS__)
#define RLE_LOG_INFO(fmt, ...) rle::Logger::Log(rle::LogLevel::Info, fmt __VA_OPT__(,) __VA_ARGS__)
#define RLE_LOG_WARN(fmt, ...) rle::Logger::Log(rle::LogLevel::Warn, fmt __VA_OPT__(,) __VA_ARGS__)
#define RLE_LOG_ERROR(fmt, ...) rle::Logger::LogAt(rle::LogLevel::Error, __FILE__, __LINE__, fmt __VA_OPT__(,) __VA_ARGS__)
#define RLE_LOG_FATAL(fmt, ...) rle::Logger::LogAt(rle::LogLevel::Fatal, __FILE__, __LINE__, fmt __VA_OPT__(,) __VA_ARGS__)