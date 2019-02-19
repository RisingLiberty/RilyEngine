#pragma once

namespace Resources
{


enum class ResourceType
{
	TEXT_FILE,
	VERTEX_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER
};

class Resource
{
public:
	Resource(const std::string& path);
	virtual ~Resource();

	std::string GetPath() const { return m_Path; }
	std::string GetName() const { return m_Name; }
	std::string GetExtention() const { return m_Name.substr(m_Name.find_last_of('.')); }
	std::string GetFullPath() const { return m_Path + m_Name; }

	virtual bool Exists() = 0;

protected:
	std::string m_Path;
	std::string m_Name;
};

}
