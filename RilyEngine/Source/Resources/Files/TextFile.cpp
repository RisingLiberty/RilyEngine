#include "stdafx.h"

#include "TextFile.h"

namespace Resources
{


TextFile::TextFile(const std::string& path):
File(path)
{
}

TextFile::TextFile(const TextFile& textFile) :
	File(textFile.m_Path)
{
}

TextFile::~TextFile()
{
}

std::string TextFile::ReadFullFile()
{
	this->Open(std::ios::in);

	while (!this->EndOfFile())
		m_Content << this->ReadLine() << "\n";

	this->Close();
	return m_Content.str();
}

}
