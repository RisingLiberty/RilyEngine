#pragma once

#define ID_IGNORE INT_MAX

#undef ERROR
namespace Debug
{
	class LogWrapper
	{
	public:
		LogWrapper();
		LogWrapper(const std::string& message, const Debug::LogType type, const std::string& file = "", const std::string& function = "", const int line = 0, const int id = ID_IGNORE);
		LogWrapper(const LogWrapper& log);
		LogWrapper& operator=(const LogWrapper& log);
		~LogWrapper();

		std::string ToString() const { return Message; }
		void Clear() { Message = ""; }
		uint_t Hash() const;

	public:
		std::string Message;
		LogType Type;
		std::string File;
		std::string Function;
		int Line = 0;
		int Id = 0;
	};
}