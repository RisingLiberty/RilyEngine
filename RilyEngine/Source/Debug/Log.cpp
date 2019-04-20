#include "stdafx.h"

#include "Log.h"

namespace Debug
{
	LogWrapper::LogWrapper()
	{
	}

	LogWrapper::LogWrapper(const std::string& message, const Debug::LogType type, const std::string& file, const std::string& function, const int line, const int id) :
		Message(message),
		File(file),
		Function(function),
		Line(line),
		Type(type), 
		Id(id)
	{
	}

	LogWrapper::LogWrapper(const LogWrapper& log) :
		Message(log.Message),
		File(log.File),
		Function(log.Function),
		Line(log.Line),
		Type(log.Type),
		Id(log.Id)
	{
	}

	LogWrapper::~LogWrapper()
	{
	}

	class LogWrapper& LogWrapper::operator=(const LogWrapper& log)
	{
		Message = log.Message;
		File = log.File;
		Function = log.Function;
		Line = log.Line;
		Type = log.Type;
		Id = log.Id;

		return *this;
	}

	uint_t LogWrapper::Hash() const
	{
		return std::hash<std::string>()(Message);
	}
}