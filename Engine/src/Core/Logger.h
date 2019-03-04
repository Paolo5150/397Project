#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Logger
{
public:
	static void Initialize();
	static void LogOut(...);
	static std::shared_ptr<spdlog::logger> GetLogger();

private:
	static std::shared_ptr<spdlog::logger> s_logger;
};

#define LOG_INFO(...) Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...) Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::GetLogger()->error(__VA_ARGS__)