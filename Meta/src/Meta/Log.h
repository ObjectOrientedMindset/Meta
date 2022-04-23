#pragma once



#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Meta {

	class META_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define MT_CORE_TRACE(...) ::Meta::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MT_CORE_INFO(...)  ::Meta::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MT_CORE_WARN(...)  ::Meta::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MT_CORE_ERROR(...) ::Meta::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MT_CORE_FATAL(...) ::Meta::Log::GetCoreLogger()->fatal(__VA_ARGS__)


//Client log macros
#define MT_TRACE(...)      ::Meta::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MT_INFO(...)       ::Meta::Log::GetClientLogger()->info(__VA_ARGS__)
#define MT_WARN(...)       ::Meta::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MT_ERROR(...)      ::Meta::Log::GetClientLogger()->error(__VA_ARGS__)
#define MT_FATAL(...)      ::Meta::Log::GetClientLogger()->fatal(__VA_ARGS__)


