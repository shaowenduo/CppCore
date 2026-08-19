#include "Logger.h"

int main() {
    Logger::info("test start");
    Logger::warning("test warning");
    Logger::error("test error");
    Logger::setLevel(LogLevel::Warning);
    Logger::info("test start");
    Logger::warning("test warning");
    Logger::error("test error");
    Logger::setLevel(LogLevel::Error);
    Logger::info("test start");
    Logger::warning("test warning");
    Logger::error("test error");
    return 0;
}