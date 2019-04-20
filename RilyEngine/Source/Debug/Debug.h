#pragma once

namespace Debug
{
#define ERROR_CODE_FILE_LOG(message, type, file, function, line, errorCode) FileLog(type, file, function, line, errorCode, message)
#define FILE_LOG(message, type, file, function, line) ERROR_CODE_FILE_LOG(message, type, file, function, line, INT_MAX);

#define PUSH_LOG_ID(message, type, id) ERROR_CODE_FILE_LOG(message, type, __FILE__, __FUNCTION__, __LINE__, id)
#define PUSH_LOG(message, type) PUSH_LOG_ID(message, type, INT_MAX)

#define PUSH_ERROR_ID(message, id) PUSH_LOG_ID(message, Debug::LogType::ERROR, id)
#define PUSH_WARNING_ID(message, id) PUSH_LOG_ID(message, Debug::LogType::WARNING, id)
#define PUSH_ERROR(message) PUSH_LOG(message, Debug::LogType::ERROR)
#define PUSH_WARNING(message) PUSH_LOG(message, Debug::LogType::WARNING)
#define PUSH_INFO(message) PUSH_LOG(message, Debug::LogType::INFO)

#define LOG(type, ...) Log(type, __VA_ARGS__)

#define BreakHere __debugbreak()

	void NewLine();
	void ClearScreen();

	template<typename... Args>
	void ForceLog(LogType type, const Args&... args)
	{
		std::ostringstream msg;
		LogRecursive(type, true, msg, args...);
	}

	template<typename... Args>
	void Log(LogType type, const Args&... args)
	{
		std::ostringstream msg;
		LogRecursive(type, false, msg, args...);
	}

	template<typename... Args>
	void LogInfo(const Args&... args)
	{
		Log(LogType::INFO, args...);
	}

	template<typename... Args>
	void LogWarning(const Args&... args)
	{
		Log(LogType::WARNING, args...);
	}

	template<typename... Args>
	void LogError(const Args&... args)
	{
		Log(LogType::ERROR, args...);
	}

	template<typename T, typename... Args>
	void LogRecursive(LogType type, bool isForced, std::ostringstream& msg,
		T value, const Args&... args)
	{
		msg << value;
		LogRecursive(type, isForced, msg, args...);
	}

	void LogRecursive(LogType type, bool isForced, std::ostringstream& msg);

	template<typename... Args>
	void FileLog(LogType type, const char* file, const char* function, int line, int errorCode, const Args&... args)
	{
		std::ostringstream msg;
		FileLogRecursive(type, file, function, line, errorCode, msg, args...);
	}

	template<typename T, typename... Args>
	void FileLogRecursive(LogType type, const char* file, const char* function, int line, int errorCode, std::ostringstream& msg,
		T value, const Args&... args)
	{
		msg << value;
		FileLogRecursive(type, file, function, line, errorCode, msg, args...);
	}

	void FileLogRecursive(LogType type, const char* file, const char* function, int line, int errorCode, std::ostringstream& msg);
}
