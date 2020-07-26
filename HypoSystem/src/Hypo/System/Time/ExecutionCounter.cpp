#include "systempch.h"
#include "ExecutionCounter.h"

namespace Hypo
{
	ExecutionCounter::ExecutionCounter()
	{
		Begin();
	}

	ExecutionCounter::ExecutionCounter(std::string name)
		: m_Name(name)
	{
		Begin();
	}

	ExecutionCounter::ExecutionCounter(std::string name, OutputFunc outputFunc, SubOuputFunc subOutputFunc)
		:m_Name(name), m_OutputFunc(outputFunc), m_SubOutputFunc(subOutputFunc)
	{
		Begin();
	}

	ExecutionCounter::~ExecutionCounter()
	{
		if(m_Running)
		{
			Stop();
		}
	}

	void ExecutionCounter::SubOperation(std::string name)
	{
		m_SubOutputFunc(m_Clock.GetElapsedTime(), m_SubClock.Reset(), m_Name, name);
	}

	void ExecutionCounter::Stop()
	{
		m_OutputFunc(m_Clock.Reset(), m_Name);
		m_Running = false;
	}

	void ExecutionCounter::Begin()
	{
		std::cout << "Starting timer for operation: " << m_Name << std::endl;
	}
}
