#pragma once
#include "../Files/File.h"

namespace Resources
{


enum class ShaderType
{
	VERTEX,
	GEOMETRY,
	FRAGMENT
};

class ShaderSource : public File
{
public:
	ShaderSource(const std::string& path, const ShaderType type);
	virtual ~ShaderSource();

	int LoadCode();

	bool HasCode() const { return !m_Code.empty(); };

	unsigned int GetType() const { return m_Type; }
	std::string GetCode() const { return m_Code; }

private:
	unsigned int m_Type;
	std::string m_Code;
};


}
