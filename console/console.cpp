#include <Windows.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <cstdarg>
#include <memory>
#include <atomic>

#include "console.hpp"

namespace Console {
    // Threading and synchronization
    static std::thread logThread;
    static std::mutex logMutex;
    static std::queue<LogEntry> logQueue;
    static std::atomic<bool> shouldStop{ false };
    static std::atomic<bool> isLogging{ false };

    // File streams
    static std::ofstream debugFile;
    static std::ofstream rpcFile;
    static std::ofstream functionFile;
    static std::ofstream healthFile;
    static std::ofstream ammoFile;
    static std::ofstream shieldFile;

    // Internal helper functions
    std::string FormatString(const char* format, va_list args) {
        va_list argsCopy;
        va_copy(argsCopy, args);

        int size = vsnprintf(nullptr, 0, format, args) + 1;
        std::unique_ptr<char[]> buffer(new char[size]);
        vsnprintf(buffer.get(), size, format, argsCopy);

        va_end(argsCopy);
        return std::string(buffer.get());
    }

    void AddToQueue(const std::string& category, const std::string& message) {
        if (!isLogging) return;

        std::lock_guard<std::mutex> lock(logMutex);
        logQueue.emplace(category, message);
    }

    void ProcessLogQueue() {
        while (!shouldStop) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            std::lock_guard<std::mutex> lock(logMutex);
            while (!logQueue.empty()) {
                const auto& entry = logQueue.front();
                WriteToFile(entry);
                logQueue.pop();
            }
        }

        // Process remaining entries
        std::lock_guard<std::mutex> lock(logMutex);
        while (!logQueue.empty()) {
            const auto& entry = logQueue.front();
            WriteToFile(entry);
            logQueue.pop();
        }
    }

    void WriteToFile(const LogEntry& entry) {
        std::ofstream* targetFile = nullptr;

        if (entry.category == "RPC") {
            targetFile = &rpcFile;
        }
        else if (entry.category == "FUNCTION") {
            targetFile = &functionFile;
        }
        else if (entry.category == "HEALTH") {
            targetFile = &healthFile;
        }
        else if (entry.category == "AMMO") {
            targetFile = &ammoFile;
        }
        else if (entry.category == "SHIELD") {
            targetFile = &shieldFile;
        }
        else {
            targetFile = &debugFile;
        }

        if (targetFile && targetFile->is_open()) {
            *targetFile << "[" << entry.timestamp << "] "
                << "[" << entry.category << "] "
                << entry.message << std::endl;
            targetFile->flush();
        }
    }
}

void Console::Alloc() {
#ifndef DISABLE_LOGGING_CONSOLE
    AllocConsole();

    SetConsoleTitleA("Debug Console - RPC Monitor");

    freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);

    ::ShowWindow(GetConsoleWindow(), SW_SHOW);
#else

#endif

    StartFileLogging();

    // Test logging on startup
    TestLogging();
}

void Console::Free() {
#ifndef DISABLE_LOGGING_CONSOLE
    fclose(stdin);
    fclose(stdout);
    FreeConsole();
#endif

    StopFileLogging();
}

void Console::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[DEBUG] %s\n", message.c_str());
#endif

    AddToQueue("DEBUG", message);
}

void Console::LogRPC(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[RPC] %s\n", message.c_str());
#endif

    AddToQueue("RPC", message);
}

void Console::LogFunction(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[FUNCTION] %s\n", message.c_str());
#endif

    AddToQueue("FUNCTION", message);
}

void Console::LogHealth(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[HEALTH] %s\n", message.c_str());
#endif

    AddToQueue("HEALTH", message);
}

void Console::LogAmmo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[AMMO] %s\n", message.c_str());
#endif

    AddToQueue("AMMO", message);
}

void Console::LogShield(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[SHIELD] %s\n", message.c_str());
#endif

    AddToQueue("SHIELD", message);
}

void Console::LogDebug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatString(format, args);
    va_end(args);

#ifndef DISABLE_LOGGING_CONSOLE
    printf("[DEBUG] %s\n", message.c_str());
#endif

    AddToQueue("DEBUG", message);
}

void Console::StartFileLogging() {
    if (isLogging) return;

    // Create log files
    debugFile.open("TOOL_DEBUG_LOG.txt", std::ios::app);
    rpcFile.open("RPC_LOGS.txt", std::ios::app);
    functionFile.open("FUNCTION_LOGS.txt", std::ios::app);
    healthFile.open("TOOL_HEALTH_LOG.txt", std::ios::app);
    ammoFile.open("TOOL_AMMO_LOG.txt", std::ios::app);
    shieldFile.open("TOOL_SHIELD_LOG.txt", std::ios::app);

    if (debugFile.is_open()) {
        debugFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }
    if (rpcFile.is_open()) {
        rpcFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }
    if (functionFile.is_open()) {
        functionFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }
    if (healthFile.is_open()) {
        healthFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }
    if (ammoFile.is_open()) {
        ammoFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }
    if (shieldFile.is_open()) {
        shieldFile << "\n=== NEW SESSION STARTED ===" << std::endl;
    }

    shouldStop = false;
    isLogging = true;
    logThread = std::thread(ProcessLogQueue);
}

void Console::StopFileLogging() {
    if (!isLogging) return;

    shouldStop = true;
    isLogging = false;

    if (logThread.joinable()) {
        logThread.join();
    }

    // Close files
    if (debugFile.is_open()) {
        debugFile << "=== SESSION ENDED ===" << std::endl;
        debugFile.close();
    }
    if (rpcFile.is_open()) {
        rpcFile << "=== SESSION ENDED ===" << std::endl;
        rpcFile.close();
    }
    if (functionFile.is_open()) {
        functionFile << "=== SESSION ENDED ===" << std::endl;
        functionFile.close();
    }
    if (healthFile.is_open()) {
        healthFile << "=== SESSION ENDED ===" << std::endl;
        healthFile.close();
    }
    if (ammoFile.is_open()) {
        ammoFile << "=== SESSION ENDED ===" << std::endl;
        ammoFile.close();
    }
    if (shieldFile.is_open()) {
        shieldFile << "=== SESSION ENDED ===" << std::endl;
        shieldFile.close();
    }
}

void Console::FlushLogs() {
    std::lock_guard<std::mutex> lock(logMutex);

    if (debugFile.is_open()) debugFile.flush();
    if (rpcFile.is_open()) rpcFile.flush();
    if (functionFile.is_open()) functionFile.flush();
    if (healthFile.is_open()) healthFile.flush();
    if (ammoFile.is_open()) ammoFile.flush();
    if (shieldFile.is_open()) shieldFile.flush();
}

void Console::TestLogging() {
    LOG("Debug Console initialized successfully");
    LOG_RPC("RPC monitoring system started");
    LOG_FUNCTION("Function monitoring system started");
    LOG_HEALTH("Health monitoring system started");
    LOG_AMMO("Ammo monitoring system started");
    LOG_SHIELD("Shield monitoring system started");
    LOG_DEBUG("Debug logging system started");

    // Give threading a moment to process
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    FlushLogs();
}