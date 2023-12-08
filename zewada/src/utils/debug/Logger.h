#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream> 

#define LOGGER_INFO 0
#define LOGGER_WARNING 1
#define LOGGER_ERROR 2

#define Z_INFO() Log(LOGGER_INFO)
#define Z_WARN() Log(LOGGER_WARNING)
#define Z_ERROR() Log(LOGGER_ERROR)

namespace Zewada{

	struct Log
	{
	public:
		void Init()
		{

		}
	private:
		HANDLE m_console;
	public:
		Log(int level)
		{
			m_console = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case LOGGER_INFO:
				SetConsoleTextAttribute(m_console, 15);
				std::cout << "[INFO]";
				break;
			case LOGGER_WARNING:
				SetConsoleTextAttribute(m_console, 14);
				std::cout << "[WARN]";
				break;
			case LOGGER_ERROR:
				SetConsoleTextAttribute(m_console, 12);
				std::cout << "[ERROR]";
				break;
			}
		}

		~Log()
		{
			std::cout << std::endl;
			SetConsoleTextAttribute(m_console, 15);
		}

		template <typename T>
		Log& operator<<(const T& t)
		{
			std::cout << " " << t;
			return *this;
		}
	};

	class Logger
	{
	private:
		std::stringstream m_log;
		std::streambuf* m_old;
	public:
		Logger();
		~Logger();

		const std::string GetLog();

	};
}


