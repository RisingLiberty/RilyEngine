#include "stdafx.h"

#include "ShaderSource.h"

#include "../Files/TextFile.h"

namespace Resources
{


ShaderSource::ShaderSource(const std::string& path, const ShaderType type):
	File(path)
{
	switch (type)
	{
	case ShaderType::VERTEX: m_Type = GL_VERTEX_SHADER; break;
	case ShaderType::GEOMETRY: m_Type = GL_GEOMETRY_SHADER; break;
	case ShaderType::FRAGMENT: m_Type = GL_FRAGMENT_SHADER; break;

	default: ASSERT(false, "No Valid shader type"); break;
	}
}


ShaderSource::~ShaderSource()
{
}

int ShaderSource::LoadCode()
{
	TextFile file(this->GetFullPath());
	file.Open(std::ios::in);

	if (!file.IsOpen())
	{
		Debug::Log(Debug::LogType::WARNING, "Failed to open shader: ", m_Name, "\nat", m_Path);
		return COULD_NOT_OPEN_RESOURCE;
	}
	
	while (!file.EndOfFile())
		m_Code += file.ReadLine() + "\n";

	file.Close();

	return OK;
}

}
