#pragma once

#include <chrono>

namespace Zewada {

	class Time
	{
	public:
		std::chrono::system_clock::time_point timeStarted;

		void StartTime()
		{
			timeStarted = std::chrono::system_clock::now();
		}
 
		float GetTime()
		{
			return (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timeStarted).count() / 1000;
		}
	};
}