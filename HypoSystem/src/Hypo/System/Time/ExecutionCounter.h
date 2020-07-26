#pragma once
#include "Clock.h"
#include "Hypo/System/Exports.h"
#include <string>
#include <functional>
#include <sstream>
#include "Time.h"
#include <iostream>

namespace Hypo
{


	static std::function<void(Time, std::string)> DefaultExecutionCounterOutputFunc = [](Time time, std::string name)
	{
		std::stringstream ss;
		ss << "Operation: " << name << " took: " << time.AsSeconds() << " to complete\n";
		std::cout << ss.str();
	};

	static std::function<void(Time, Time, std::string, std::string)> DefaultExecutionCounterSubOutputFunc = [](Time time, Time subTime, std::string name,std::string subName)
	{
		std::stringstream ss;
		ss << "\tSub Operation: " << subName << " for: " << name << " took: " << subTime.AsSeconds() << " to complete: " << time.AsSeconds() << " in total\n";
		std::cout << ss.str();
	};
	/**
	 * \brief Used to time different operations also supports sub operation too enable more detailed outputs
	 */
	class HYPO_SYSTEM_API ExecutionCounter
{	
	public:
		using OutputFunc = std::function<void(Time, std::string)>;
		using SubOuputFunc = std::function<void(Time, Time, std::string, std::string)>;

		ExecutionCounter();
		ExecutionCounter(std::string name);
		ExecutionCounter(std::string name, OutputFunc outputFunc, SubOuputFunc subOutputFunc);
		~ExecutionCounter();
	
		void SubOperation(std::string name);
		void Stop();

	private:
		void Begin();
		OutputFunc m_OutputFunc = DefaultExecutionCounterOutputFunc;
		SubOuputFunc m_SubOutputFunc = DefaultExecutionCounterSubOutputFunc;
		std::string m_Name = "ExecutionCounter";

		Clock m_Clock;
		Clock m_SubClock;
		bool m_Running = true;
	};

}
