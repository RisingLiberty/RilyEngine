#include "stdafx.h"

#include "File.h"

namespace Resources
{


File::File(const std::string& path) :
	Resource(path)
{
}


File::~File()
{
}

void File::Open(int mode)
{
	m_File.open(GetFullPath(), mode);
}

bool File::Exists()
{
	this->Open(std::ios::in);
	if (this->IsOpen())
	{
		this->Close();
		return true;
	}
	return false;
}

void File::Close()
{
	m_File.close();
}

}