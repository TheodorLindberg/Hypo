#pragma once
#include <algorithm>
#include <numeric>
#include <array>

namespace Hypo
{
	class FPSCounter
	{
	public:
		int PeakFPS = 0;
		int LowFPS = 0;
		int AverageFPS = 0;
		int CurrentFPS = 0;

		float PeakFrameTime = 0.f;
		float LowFrameTime = 0.f;
		float AverageFrameTime = 0.f;
		float CurrentFrameTime = 0.f;

		static constexpr int FPS_FRAME_TRACK = 60;
	private:
		std::array<float, FPS_FRAME_TRACK> m_AverageTrack;
		bool m_First = true;
		int m_Index = 0;
	public:
		void Reset()
		{
			m_Index = 0;
			m_First = true;

			PeakFPS = 0;
			LowFPS = 0;
			AverageFPS = 0;
			CurrentFPS = 0;

			PeakFrameTime = 0.f;
			LowFrameTime = 0.f;
			AverageFrameTime = 0.f;
			CurrentFrameTime = 0.f;
		}

		void Frame(float dt)
		{
			CurrentFrameTime = dt;
			CurrentFPS = static_cast<int>(1.f / dt);


			if(m_First)
			{
				std::fill(m_AverageTrack.begin(), m_AverageTrack.end(), CurrentFrameTime);
				AverageFrameTime = CurrentFrameTime;
				AverageFPS = static_cast<int>(1.f / CurrentFrameTime);

				PeakFPS = CurrentFPS;
				LowFPS = CurrentFPS;
				PeakFrameTime = CurrentFrameTime;
				LowFrameTime = CurrentFrameTime;

				m_First = false;

				return;
			}

			PeakFPS = std::max(CurrentFPS, PeakFPS);
			PeakFrameTime = std::max(CurrentFrameTime, PeakFrameTime);

			LowFPS = std::min(CurrentFPS, LowFPS);
			LowFrameTime = std::min(CurrentFrameTime, LowFrameTime);

			m_AverageTrack[m_Index] = CurrentFrameTime;

			if(m_Index % 20 == 0)
			{
				float average = std::accumulate(m_AverageTrack.begin(), m_AverageTrack.end(), 0.f) / static_cast<float>(FPS_FRAME_TRACK);
				AverageFrameTime = average;
				AverageFPS = static_cast<int>(1.f / average);
			}

			if (++m_Index > FPS_FRAME_TRACK - 1)
				m_Index = 0;
				
			
		}
	};
}