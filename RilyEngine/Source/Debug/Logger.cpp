#include "stdafx.h"

#include "Logger.h"
#include "Resources/Files/TextFile.h"


namespace Debug
{
	const std::string Logger::LOG_FILE_PATH = LOG_PATH + "RilyEngine.log";
	std::map<uint_t, class LogWrapper> Logger::s_Logs = {};
	Container::Vector<class LogWrapper> Logger::s_FileLogs = {};
	bool Logger::s_CollapseLogs = true;

	int Logger::Initialize()
	{
		ClearScreen();
		return OK;
	}

	void Logger::Log(const std::string& message, LogType type, bool isForced)
	{
		LogWrapper log(message, type);
		uint_t hash = log.Hash();

		if (s_Logs.find(hash) == s_Logs.end())
		{
			s_Logs[hash] = log;
			WriteToConsole(message, type);
		}
		else if (!s_CollapseLogs || isForced)
			WriteToConsole(message, type);
	}

	void Logger::AddFileLog(const class LogWrapper& log)
	{
		s_FileLogs.AddC(log);
	}

	void Logger::NewLine()
	{
		std::cout << "\n";
	}

	void Logger::ClearScreen()
	{
#if defined WIN32
		system("cls");
#elif defined __linux__ || defined __APPLE__
		system("clear");
#endif
	}

	void Logger::Shutdown()
	{
		Resources::TextFile outputFile = Resources::TextFile(LOG_FILE_PATH);
		outputFile.Open(std::ios::out);

		if (!outputFile.IsOpen())
		{
			Debug::Logger::LogError("Can not open event log file");
			assert(false);
			return;
		}

		outputFile << TimeAndDateToString() << "\n\n";

		for (const class LogWrapper& log : s_FileLogs)
		{
			switch (log.Type)
			{
			case Debug::LogType::WARNING:
				WriteWarning(outputFile, log);
				break;
			case Debug::LogType::ERROR:
				WriteError(outputFile, log);
				break;
			case Debug::LogType::INFO:
				WriteInfo(outputFile, log);
				break;
			}
		}

		outputFile.Close();
	}

	void Logger::WriteToConsole(const std::string& message, const Debug::LogType type)
	{
		switch (type)
		{
		case Debug::LogType::INFO:
			LogInfo(message);
			break;
		case Debug::LogType::WARNING:
			LogWarning(message);
			break;
		case Debug::LogType::ERROR:
			LogError(message);
			break;
		case Debug::LogType::FORCE:
			ForceLog(message);
			break;
		}
	}

	void Logger::WriteError(Resources::TextFile& output, const class LogWrapper& log)
	{
		output << "\n------------------------------------\n";
		output << "File: " << log.File << "\n";
		output << "Function: " << log.Function << "\n";
		output << "Line: " << log.Line << "\n";
		if (log.Id != ID_IGNORE)
			output << "ID: " << log.Id << "\n";
		output << "[" << TimeToString() << "] <Error> " << log.ToString() << "\n";

		output << "------------------------------------\n";
	}

	void Logger::WriteWarning(Resources::TextFile& output, const class LogWrapper& log)
	{
		output << "\n------------------------------------\n";
		output << "File: " << log.File << "\n";
		output << "Function: " << log.Function << "\n";
		output << "Line: " << log.Line << "\n";
		if (log.Id != ID_IGNORE)
			output << "ID: " << log.Id << "\n";
		output << "[" << TimeToString() << "] <Warning> " << log.ToString() << "\n";

		output << "------------------------------------\n";
	}

	void Logger::WriteInfo(Resources::TextFile& output, const class LogWrapper& log)
	{
		output << "[" << TimeToString() << "] <Info> " << log.ToString() << "\n";
	}

}