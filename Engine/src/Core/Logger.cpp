#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_logger;

void Logger::Initialize()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_logger = spdlog::stdout_color_mt("Engine:");

}



std::shared_ptr<spdlog::logger> Logger::GetLogger()
{
	return s_logger;
}