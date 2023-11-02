#pragma once

#include <string>
#include <iostream>

#define LOGGER_INFO 0
#define LOGGER_WARNING 1
#define LOGGER_ERROR 2

#define Z_INFO(msg) Log(msg, LOGGER_INFO)
#define Z_WARN(msg) Log(msg, LOGGER_WARNING)
#define Z_ERROR(msg) Log(msg, LOGGER_ERROR)

namespace Zewada{
	class Log
	{
	public:
		template<typename T>
		Log(T msg, int level)
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case LOGGER_INFO:
				SetConsoleTextAttribute(console, 15);
				std::cout << "[INFO] " << msg << std::endl;
				break;
			case LOGGER_WARNING:
				SetConsoleTextAttribute(console, 14);
				std::cout << "[WARN] " << msg << std::endl;
				SetConsoleTextAttribute(console, 15);
				break;
			case LOGGER_ERROR:
				SetConsoleTextAttribute(console, 12);
				std::cout << "[ERROR] " << msg << std::endl;
				SetConsoleTextAttribute(console, 15);
				break;
			}
		}
	};
}


