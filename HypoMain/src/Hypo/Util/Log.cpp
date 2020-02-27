#include "mainpch.h"

#pragma warning( push )
#pragma warning(disable: 26451)
#pragma warning(disable: 6387)
#pragma warning(disable: 26498)
#pragma warning(disable: 26495)

#include "Log.h"
#include <spdlog/logger.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Hypo
{

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::time_t Log::s_StartTime;
	Log::LogCount Log::s_CoreLogCounter;
	Log::LogCount Log::s_ClientLogCounter;

	void Log::Init()
	{

		std::string logOutputDir = "../logs";

		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_pattern("%^[%H:%M:%S:%e] [%n] [%l] %n%v%$");
		time_t curr_time;
		tm * curr_tm;
		char date_string[100];

		time(&curr_time);
	
		s_StartTime = curr_time;

		curr_tm = localtime(&curr_time);

		std::stringstream outputFile;
		outputFile << logOutputDir;
		outputFile << "/";

		strftime(date_string, sizeof(date_string), "%Y-%m-%d_%H-%M-%S", curr_tm);
		outputFile << date_string;
		outputFile << ".txt";
		auto str = outputFile.str();

		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(str.c_str(), true);
		file_sink->set_pattern("%^[%c] [%n] [%l] %n%v%$");
	
		s_CoreLogger = std::make_shared<spdlog::logger>("Hypo", spdlog::sinks_init_list{ console_sink, file_sink });
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::err);

		s_ClientLogger = std::make_shared<spdlog::logger>("Client", spdlog::sinks_init_list{ console_sink, file_sink });
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::err);

	}

	void Log::Shutdown()
	{


		time_t curr_time;
		time(&curr_time);

		std::time_t executionTime = curr_time - s_StartTime;

		s_CoreLogger->set_pattern("%v");
		s_ClientLogger->trace("");
		s_CoreLogger->set_pattern("[%c] [Shutdown] %v");
		s_CoreLogger->trace("Application shutting down");
		s_CoreLogger->trace("Application ran for {0} seconds", executionTime);
		s_CoreLogger->trace("Core logger had {0} traces, {1} debugs, {2} infos, {3} warnings, {4} errors, {5} criticals", 
			s_CoreLogCounter.traces, s_CoreLogCounter.debugs, s_CoreLogCounter.infos, s_CoreLogCounter.warns, s_CoreLogCounter.errors, s_CoreLogCounter.criticals);

		s_CoreLogger->trace("Client logger had {0} traces, {1} debugs, {2} infos, {3} warnings, {4} errors, {5} criticals",
			s_CoreLogCounter.traces, s_CoreLogCounter.debugs, s_CoreLogCounter.infos, s_CoreLogCounter.warns, s_CoreLogCounter.errors, s_CoreLogCounter.criticals);

		s_CoreLogger->flush();
		s_ClientLogger->flush();

		s_ClientLogger.reset();
		s_CoreLogger.reset();
	}
}


#pragma warning( pop ) 