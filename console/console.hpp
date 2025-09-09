#pragma once
#include <cstdio>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>

#define DISABLE_LOGGING_CONSOLE

// Configuration for extensive logging
// #define ENABLE_EXTENSIVE_RPC_LOGGING true

#ifndef DISABLE_LOGGING_CONSOLE
#define LOG(...) Console::Log(__VA_ARGS__)
#else
#define LOG(...)
#endif

// Specialized logging macros for different types
#ifndef DISABLE_LOGGING_CONSOLE
#define LOG_RPC(...) Console::LogRPC(__VA_ARGS__)
#define LOG_FUNCTION(...) Console::LogFunction(__VA_ARGS__)
#define LOG_HEALTH(...) Console::LogHealth(__VA_ARGS__)
#define LOG_AMMO(...) Console::LogAmmo(__VA_ARGS__)
#define LOG_SHIELD(...) Console::LogShield(__VA_ARGS__)
#define LOG_DEBUG(...) Console::LogDebug(__VA_ARGS__)
#else
#define LOG_RPC(...)
#define LOG_FUNCTION(...)
#define LOG_HEALTH(...)
#define LOG_AMMO(...)
#define LOG_SHIELD(...)
#define LOG_DEBUG(...)
#endif

// Conditional logging for extensive monitoring
#if ENABLE_EXTENSIVE_RPC_LOGGING && !defined(DISABLE_LOGGING_CONSOLE)
#define LOG_RPC_EXTENSIVE(...) Console::LogRPC(__VA_ARGS__)
#define LOG_HEALTH_EXTENSIVE(...) Console::LogHealth(__VA_ARGS__)
#define LOG_AMMO_EXTENSIVE(...) Console::LogAmmo(__VA_ARGS__)
#define LOG_SHIELD_EXTENSIVE(...) Console::LogShield(__VA_ARGS__)
#else
#define LOG_RPC_EXTENSIVE(...)
#define LOG_HEALTH_EXTENSIVE(...)
#define LOG_AMMO_EXTENSIVE(...)
#define LOG_SHIELD_EXTENSIVE(...)
#endif

namespace Console {
    // Core functions
    void Alloc();
    void Free();

    // Enhanced logging functions
    void Log(const char* format, ...);
    void LogRPC(const char* format, ...);
    void LogFunction(const char* format, ...);
    void LogHealth(const char* format, ...);
    void LogAmmo(const char* format, ...);
    void LogShield(const char* format, ...);
    void LogDebug(const char* format, ...);

    // File logging control
    void StartFileLogging();
    void StopFileLogging();
    void FlushLogs();

    // Test function
    void TestLogging();

    // Internal logging structure
    struct LogEntry {
        std::string timestamp;
        std::string category;
        std::string message;

        LogEntry(const std::string& cat, const std::string& msg)
            : category(cat), message(msg) {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % 1000;

            std::stringstream ss;
            ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
            timestamp = ss.str();
        }
    };

    // Internal functions
    void ProcessLogQueue();
    void WriteToFile(const LogEntry& entry);
    std::string GetTimestamp();
}