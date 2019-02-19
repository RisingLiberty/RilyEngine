#include "stdafx.h"

#include "ShaderProgram.h"
#include "Shader.h"

#include "../Context/Context.h"

namespace Graphics::Shader
{


ShaderProgram::ShaderProgram(const std::string& name):
	m_Name(name)
{
}

ShaderProgram::ShaderProgram(const ShaderProgram& program):
	m_Name(program.m_Name)
{

}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(m_ID));
}

int ShaderProgram::Create(const Container::Vector<unsigned int>& shaderIDs)
{
	GLCall(m_ID = glCreateProgram());

	for (unsigned int id : shaderIDs)
	{
		GLCall(glAttachShader(m_ID, id));
	}

	GLCall(glLinkProgram(m_ID));
	GLCall(glValidateProgram(m_ID));

	int result = GL_FALSE;
	int messageLength = 0;

	GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &result));
	GLCall(glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &messageLength));

	if (messageLength > 0)
	{
		std::string error;
		error.resize(messageLength);
		GLCall(glGetProgramInfoLog(m_ID, messageLength, nullptr, error.data()));
		Debug::Log(Debug::LogType::ERROR, error);
		return result;
	}

	return OK;
}

void ShaderProgram::Bind() const
{
	Context::Context::GetCurrent()->BindShader(m_ID);
}

void ShaderProgram::UnBind() const
{
	Context::Context::GetCurrent()->BindShader(0);
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_ID, name.c_str()));
	if (location == -1)
	{
		Debug::Log(Debug::LogType::WARNING, "Uniform '", name, "' not found in shader or doesn't exists\nShader file: ", m_Name);
		return UNIFORM_NOT_FOUND;
	}
	
	m_UniformLocationCache[name] = location;
	return location;
}

Container::Vector<Uniform> ShaderProgram::GetUniforms() const
{
	int count;
	GLCall(glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &count));

	Container::Vector<Uniform> uniforms;

	for (int i = 0; i < count; ++i)
	{
		GLint Count;
		GLenum type;

		const GLsizei bufSize = 16; //maximum name length
		GLchar name[bufSize]; //uniform name
		GLsizei nameLength; //uniform name length

		GLCall(glGetActiveUniform(m_ID, i, bufSize, &nameLength, &Count, &type, name));

		uniforms.AddM(Uniform(Count, type, name));
	}

	return uniforms;
}

}