#pragma once

#include "Uniform.h"

namespace Graphics::Shader
{


class ShaderProgram
{
public:
	ShaderProgram(const std::string& name);
	ShaderProgram(const ShaderProgram& program);
	~ShaderProgram();

	int Create(const Container::Vector<unsigned int>& shaders);

	void Bind() const;
	void UnBind() const;

	unsigned int GetID() const { return m_ID; }
	std::string GetName() const { return m_Name; }

	template <typename T>
	void SetUniform(const std::string& name, const T& uniform)
	{
		assert(false && "SetUniform method not overriden with correct method yet");
	}

	template <>
	void SetUniform<float>(const std::string& name, const float& uniform)
	{
		GLCall(glUniform1f(GetUniformLocation(name), uniform));
	}

	template <>
	void SetUniform<int>(const std::string& name, const int& uniform)
	{
		GLCall(glUniform1i(GetUniformLocation(name), uniform));
	}

	template <>
	void SetUniform<Math::Vec2>(const std::string& name, const Math::Vec2& vec)
	{
		GLCall(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
	}

	template <>
	void SetUniform<Math::Vec3>(const std::string& name, const Math::Vec3& vec)
	{
		GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	template <>
	void SetUniform<Math::Vec4>(const std::string& name, const Math::Vec4& vec)
	{
		GLCall(glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	template <>
	void SetUniform<Math::Mat44>(const std::string& name, const Math::Mat44& mat)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat.m[0][0]));
	}

	int GetUniformLocation(const std::string& name);

	Container::Vector<Uniform> GetUniforms() const;

private:

private:
	unsigned int m_ID;
	std::string m_Name;
	std::map<std::string, int> m_UniformLocationCache;
};

}
