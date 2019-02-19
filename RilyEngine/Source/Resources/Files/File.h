#pragma once

#include "../Resource.h"

namespace Resources
{


class File : public Resource
{
public:
	File(const std::string& path);
	virtual ~File();

	virtual bool Exists() override;
	virtual void Open(int mode);

	bool EndOfFile() const { return m_File.eof(); }
	bool IsOpen() const { return m_File.is_open(); }
	void Close();

protected:
	std::fstream m_File;
};

}
