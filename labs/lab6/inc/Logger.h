#pragma once
#include <fstream>
#include <iostream>
#include <windows.h>
#include <time.h>

enum class LogLevel
{
	DEBUG,
	RELEASE
};

HANDLE static hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
time_t static my_time = time(NULL);

class Log
{
private:
	static std::ofstream m_out;
	static LogLevel m_logLevel;
public:
	static void SetLogLevel(LogLevel logLevel)
	{
		m_logLevel = logLevel;
	}

	static void SetLogPath(const std::string& path)
	{
		m_out.open(path);
	}

	static void Write(const std::string& msg)
	{

		if (m_logLevel == LogLevel::DEBUG)
			std::cerr << ctime(&my_time) << msg << std::endl;
		m_out << ctime(&my_time) << std::endl;
		m_out << msg << std::endl;
		m_out.flush();
	}

	static void Info(const std::string& msg)
	{
		if (m_logLevel == LogLevel::DEBUG) {
			SetConsoleTextAttribute(hStdOut, 1);
			std::cerr << ctime(&my_time) << msg << std::endl;
			SetConsoleTextAttribute(hStdOut, 15);
		}
		m_out << ctime(&my_time) << std::endl;
		m_out << msg << std::endl;
		m_out.flush();
	}

	static void Debug(const std::string& msg)
	{
		if (m_logLevel == LogLevel::DEBUG) {
			SetConsoleTextAttribute(hStdOut, 14);
			std::cerr << ctime(&my_time) << msg << std::endl;
			SetConsoleTextAttribute(hStdOut, 15);
		}
		m_out << ctime(&my_time) << std::endl;
		m_out << msg << std::endl;
		m_out.flush();
	}

	static void Error(const std::string& msg)
	{
		if (m_logLevel == LogLevel::DEBUG) {
			SetConsoleTextAttribute(hStdOut, 4);
			std::cerr << ctime(&my_time) << msg << std::endl;
			SetConsoleTextAttribute(hStdOut, 15);
		}
		m_out << ctime(&my_time) << std::endl;
		m_out << msg << std::endl;
		m_out.flush();
	}
};
