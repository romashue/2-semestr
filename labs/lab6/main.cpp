#include <iostream>
#include "Logger.h"
#include <time.h>

int main()
{
	Log::SetLogPath("log.txt");
	Log::SetLogLevel(LogLevel::DEBUG);
	Log::Write("2222");
	Log::Info("Info");
	Log::Debug("Debug");
	Log::Error("Error");

	return 0;
}