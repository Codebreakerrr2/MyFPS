#include <gtest/gtest.h>
#include <profiling/FileLogger.h>

#include "profiling/LoggerManager.h"
#include "profiling/ConsoleLogger.h"

TEST(LoggerManagerTest, SingletonInstance) {
    auto& instance1 = Logging::LoggerManager::Get();
    auto& instance2 = Logging::LoggerManager::Get();

    EXPECT_EQ(&instance1, &instance2);
}
TEST(LoggerManagerTest, ConsoleLoggingWorks) {
    using namespace Logging;

    LoggerManager& logger = LoggerManager::Get();
    logger.setConsoleLog(true);
    logger.setUILog(false);
    logger.setFileLog(false);

    testing::internal::CaptureStdout();

    logger.Log("Test message", LogLevel::INFO);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("[INFO] Test message"), std::string::npos);
}
TEST(LoggerManagerTest, ConsoleLoggingDisabled) {
    using namespace Logging;

    LoggerManager& logger = LoggerManager::Get();
    logger.setConsoleLog(false);
    logger.setUILog(false);
    logger.setFileLog(false);

    testing::internal::CaptureStdout();

    logger.Log("Should not appear", LogLevel::INFO);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.empty());
}
TEST(LogLevelTest, ToStringWorks) {
    using namespace Logging;

    EXPECT_EQ(logLevelToString(LogLevel::ERROR), "[ERROR] ");
    EXPECT_EQ(logLevelToString(LogLevel::WARNING), "[WARNING] ");
    EXPECT_EQ(logLevelToString(LogLevel::INFO), "[INFO] ");
    EXPECT_EQ(logLevelToString(LogLevel::DEBUG), "[DEBUG] ");
    EXPECT_EQ(logLevelToString(LogLevel::SUCCESS), "[SUCCESS] ");
}
#include <fstream>

TEST(FileLoggerTest, WritesToFile) {
    using namespace Logging;

    std::string testFile = "test_log.txt";

    FileLogger logger(testFile);
    logger.Log("File test", LogLevel::INFO);

    std::ifstream file(testFile);
    std::string content;

    ASSERT_TRUE(file.is_open());
    std::getline(file, content);

    EXPECT_NE(content.find("File test"), std::string::npos);
}
TEST(LoggerMacroTest, MacroWorks) {
#ifdef ENGINE_DEBUG
    using namespace Logging;

    LoggerManager& logger = LoggerManager::Get();
    logger.setConsoleLog(true);
    logger.setUILog(false);
    logger.setFileLog(false);

    testing::internal::CaptureStdout();

    LOG_INFO("Macro test");

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Macro test"), std::string::npos);
#endif
}

TEST(LoggerMacroTest, MacroWorkss) {
#ifndef ENGINE_DEBUG
    GTEST_SKIP() << "ENGINE_DEBUG not defined, skipping macro test";
#endif

    using namespace Logging;

    LoggerManager& logger = LoggerManager::Get();
    logger.setConsoleLog(true);
    logger.setUILog(false);
    logger.setFileLog(false);

    // Konsole abfangen
    testing::internal::CaptureStdout();

    LOG_INFO("Macro test");

    std::string output = testing::internal::GetCapturedStdout();

    // Prüfen, ob der Text im Output ist
    EXPECT_NE(output.find("Macro test"), std::string::npos);
}