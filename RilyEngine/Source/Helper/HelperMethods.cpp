#include "stdafx.h"

#include <ctime>
#include <chrono>

#include "HelperMethods.h"

std::string TimeAndDateToString()
{
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buff[26];
	ctime_s(buff, sizeof buff, &time);
	std::string time_str(buff);
	return time_str.substr(0, time_str.length() - 1);
}

std::string TimeToString()
{
	std::string timeAndDate = TimeAndDateToString();

	const int timeBegin = 11;
	const int timeEnd = timeBegin + 8;

	return std::string(timeAndDate.begin() + timeBegin, timeAndDate.begin() + timeEnd);
}

std::string DateToString()
{
	std::string timeAndDate = TimeAndDateToString();

	const int dateFirstEnd = 10;
	const int timeEnd = dateFirstEnd + 9;

	std::string dateStr = std::string(timeAndDate.begin(), timeAndDate.begin() + dateFirstEnd);
	dateStr += " " + std::string(timeAndDate.begin() + timeEnd + 1, timeAndDate.end());

	return dateStr;
}