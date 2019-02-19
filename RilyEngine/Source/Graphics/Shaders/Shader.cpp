#include "stdafx.h"

#include "Shader.h"

#include "../../Resources/Shaders/ShaderSource.h"

namespace Graphics::Shader
{

Shader::Shader():
	m_ID(0)
{
}

Shader::~Shader()
{
}

int Shader::Compile(const Resources::ShaderSource* pSource)
{
	GLCall(m_ID = glCreateShader(pSource->GetType()));
	std::string source = pSource->GetCode();
	const char* code = source.c_str();

	GLCall(glShaderSource(m_ID, 1, &code, nullptr));
	GLCall(glCompileShader(m_ID));

	int result = GL_FALSE;
	int infoLength = 0;
	GLCall(glGetShaderiv(m_ID, GL_COMPILE_STATUS, &result));
	GLCall(glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &infoLength));

	if (infoLength > 0)
	{
		std::string message;
		message.resize(infoLength);
		GLCall(glGetShaderInfoLog(m_ID, infoLength, nullptr, message.data()));
		Debug::Log(Debug::LogType::ERROR, message, "\n");
	}

	return result;
}
}