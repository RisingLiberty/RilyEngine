#pragma once

#include "../Resources/Files/TextFile.h"
#include "Log.h"

#define COUT(x) std::cout << x << "\n";

namespace Debug
{
	class LogWrapper;

	class Logger
	{
	public:
		Logger() = delete;

#pragma region template methods
		template <typename T>
		static void LogInfo(T message)
		{
			//Set color to white
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::stringstream ss;
			ss << "[" << TimeToString() << "]" << " <Info> " << message;
			COUT(ss.str());
		}

		template <typename T>
		static void LogWarning(T message)
		{
			//Set color to yellow
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
			std::stringstream ss;
			ss << "[" << TimeToString() << "]" << " <Warning> " << message;
			COUT(ss.str());
		}

		template <typename T>
		static void LogError(T message)
		{
			//set color to red
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			std::stringstream ss;
			ss << "[" << TimeToString() << "]" << " <Error> " << message;
			COUT(ss.str());
		}

		template <typename T>
		static void ForceLog(T message)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::stringstream ss;
			ss << "[" << TimeToString() << "] " << message;
			COUT(ss.str());
		}

#pragma endregion

		static int Initialize();

		static void Log(const std::string& message, LogType type, bool isForced);
		static void NewLine();
		static void AddFileLog(const class LogWrapper& log);
		static void ClearScreen();
		static void Shutdown();

	private:
		static void WriteToConsole(const std::string& message, const LogType type = LogType::INFO);

		static void WriteError(Resources::TextFile& output, const class LogWrapper& log);
		static void WriteWarning(Resources::TextFile& output, const class LogWrapper& log);
		static void WriteInfo(Resources::TextFile& output, const class LogWrapper& log);

	private:

		static bool s_CollapseLogs;
		static std::map<uint_t, class LogWrapper> s_Logs;
		static Container::Vector<class LogWrapper> s_FileLogs;
		static const std::string LOG_FILE_PATH;
	};
}
