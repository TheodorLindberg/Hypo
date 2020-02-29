#pragma once

#include "spdlog/spdlog.h"
#include "Hypo/System/Exports.h"
#include "Hypo/System/DataTypes/ObjPtr.h"

namespace Hypo
{
	class HYPO_SYSTEM_API Log
	{
	public:
		struct LogCount
		{
			unsigned int traces = 0;
			unsigned int debugs = 0;
			unsigned int infos = 0;
			unsigned int warns = 0;
			unsigned int errors = 0;
			unsigned int criticals = 0;
		};
	public:
		static void Init();
		static void Shutdown();
		static ObjPtr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static ObjPtr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		static LogCount& GetCoreLogCounter() { return s_CoreLogCounter; }
		static LogCount& GetClientLogCounter() { return s_ClientLogCounter; }
	private:
		static time_t s_StartTime;
		static ObjPtr<spdlog::logger> s_CoreLogger;
		static ObjPtr<spdlog::logger> s_ClientLogger;

		static LogCount s_CoreLogCounter;
		static LogCount s_ClientLogCounter;
	};

}


#define HYPO_CORE_TRACE(...)      Hypo::Log::GetCoreLogger()->trace(__VA_ARGS__);      Hypo::Log::GetCoreLogCounter().traces++;
#define HYPO_CORE_DEBUG(...)      Hypo::Log::GetCoreLogger()->debug(__VA_ARGS__);      Hypo::Log::GetCoreLogCounter().debugs++;
#define HYPO_CORE_INFO(...)       Hypo::Log::GetCoreLogger()->info(__VA_ARGS__);       Hypo::Log::GetCoreLogCounter().infos++;
#define HYPO_CORE_WARN(...)       Hypo::Log::GetCoreLogger()->warn(__VA_ARGS__);       Hypo::Log::GetCoreLogCounter().warns++;
#define HYPO_CORE_ERROR(...)      Hypo::Log::GetCoreLogger()->error(__VA_ARGS__);      Hypo::Log::GetCoreLogCounter().errors++;
#define HYPO_CORE_CRITICAL(...)   Hypo::Log::GetCoreLogger()->critical(__VA_ARGS__);   Hypo::Log::GetCoreLogCounter().criticals++;

#define HYPO_APP_TRACE(...)           Hypo::Log::GetClientLogger()->trace(__VA_ARGS__);    Hypo::Log::GetClientLogCounter().traces++;
#define HYPO_APP_DEBUG(...)           Hypo::Log::GetClientLogger()->debug(__VA_ARGS__);    Hypo::Log::GetClientLogCounter().debugs++;
#define HYPO_APP_INFO(...)            Hypo::Log::GetClientLogger()->info(__VA_ARGS__);     Hypo::Log::GetClientLogCounter().infos++;
#define HYPO_APP_WARN(...)            Hypo::Log::GetClientLogger()->warn(__VA_ARGS__);     Hypo::Log::GetClientLogCounter().warns++;
#define HYPO_APP_ERROR(...)           Hypo::Log::GetClientLogger()->error(__VA_ARGS__);    Hypo::Log::GetClientLogCounter().errors++;
#define HYPO_APP_CRITICAL(...)        Hypo::Log::GetClientLogger()->critical(__VA_ARGS__); Hypo::Log::GetClientLogCounter().criticals++;
