#pragma once
#include "File.h"

namespace Resources
{


class TextFile final : public File
{
public:
	TextFile(const std::string& path);
	TextFile(const TextFile& textFile);
	~TextFile();

	std::string ReadFullFile();

	template <typename T>
	TextFile& operator<<(T message)
	{
		Write(message);
		return *this;
	}
	
	template <typename T>
	void Write(T message)
	{
		m_File << message;
	}

	std::string ReadLine()
	{
		std::string line;
		std::getline(m_File, line);
		return line;
	}
	
private:
	std::stringstream m_Content;
};

}
