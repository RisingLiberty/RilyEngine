#include "stdafx.h"

#include "Resource.h"

namespace Resources
{


Resource::Resource(const std::string& path):
	m_Path(path)
{
	std::replace(m_Path.begin(), m_Path.end(), '\\', '/');
	m_Name = m_Path.substr(m_Path.find_last_of('/'));
	m_Path = m_Path.substr(0, m_Path.find_last_of('/'));
}


Resource::~Resource()
{
}

}
