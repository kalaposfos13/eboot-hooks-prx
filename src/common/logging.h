#pragma once

#include "fmt/format.h"

// LOG_WARNING("(DUMMY) called, path: {}", pPath);

template <typename... Args>
void PrintLog(const char* log_level, const char* file, unsigned int line_num, const char* function,
              const char* format, const Args&... args) {
    std::string message;
    if constexpr (sizeof...(args) == 0) {
        message = format;  // no formatting needed
    } else {
        message = fmt::vformat(format, fmt::make_format_args(args...));
    }

    fmt::print("[PRX] {}:{} <{}> {}: {}\n", file, line_num, log_level, function, message);
}

#define LOG_DEBUG(...)    PrintLog("Debug",    __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...)     PrintLog("Info",     __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  PrintLog("Warning",  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    PrintLog("Error",    __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_CRITICAL(...) PrintLog("Critical", __FILE__, __LINE__, __func__, __VA_ARGS__)
