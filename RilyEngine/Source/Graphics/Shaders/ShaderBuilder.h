#pragma once

namespace Resources
{
	class ShaderSource;
}

namespace Graphics::Shader
{

class ShaderProgram;
class Shader;

class ShaderBuilder
{
public:
	static Shader* BuildShader(const Resources::ShaderSource* pSource);
	static ShaderProgram* CreateShaderProgram(const Container::Vector<unsigned int>& shaderIDs, const std::string& name);

private:
	ShaderBuilder() = default;
	~ShaderBuilder() = default;
};

}