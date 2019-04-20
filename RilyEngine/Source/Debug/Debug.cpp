#include "stdafx.h"

#include "Debug.h"

#include "Log.h"
#include "Logger.h"

namespace Debug
{
	void NewLine()
	{
		Logger::NewLine();
	}

	void ClearScreen()
	{
		Logger::ClearScreen();
	}

	void LogRecursive(LogType type, bool isForced, std::ostringstream& msg)
	{
		Logger::Log(msg.str(), type, isForced);
	}

	void FileLogRecursive(LogType type, const char* file, const char* function, int line, int errorCode, std::ostringstream& msg)
	{
		Logger::AddFileLog(class LogWrapper(msg.str(), type, file, function, line, errorCode));
	}
}
