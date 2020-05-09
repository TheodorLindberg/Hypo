#pragma once
namespace Hypo
{
	template<typename T>
	class FlowControl
	{
	public:
		FlowControl(std::function<bool(T&)> out)
			: m_In([](T&)->bool { return true; }),
			m_Out(out)
		{}
		FlowControl(std::function<bool(T&)> in, std::function<bool(T&)> out)
			: m_In(in),
			m_Out(out)
		{}
		inline bool In(T& data)
		{
			bool in = m_In(data);
			if (in)
			{
				return m_Out(data);
			}
			return false;
		}
		inline bool Out(T& data)
		{
			return m_Out(data);
		}

		void SetIn(std::function<bool(T&)> func) { m_In = func; }
		//void SetOut(std::function<bool(T&)> func) { m_Out = func; }
	private:
		std::function<bool(T&)> m_In;
		std::function<bool(T&)> m_Out;
	};
}