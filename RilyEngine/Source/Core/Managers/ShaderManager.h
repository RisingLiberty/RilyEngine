#pragma once
#include "../../Helper/Singleton.h"

namespace Graphics::Shader
{
class Shader;
class ShaderProgram;
}

namespace Resources
{
class ShaderSource;
}


class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	virtual ~ShaderManager();

	int Initialize();

	bool BindVertexShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource);
	bool BindGeometryShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource);
	bool BindFragmentShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource);

	bool AddProgram(Graphics::Shader::ShaderProgram* pProgram);

	Graphics::Shader::Shader* GetVertexShader(const std::string& code) const;
	Graphics::Shader::Shader* GetGeometryShader(const std::string& code) const ;
	Graphics::Shader::Shader* GetFragmentShader(const std::string& code) const;



	Graphics::Shader::ShaderProgram* GetShader(const std::string& name) const;

private:
	std::unordered_map<unsigned int, Graphics::Shader::Shader*> m_VertexShaders;
	std::unordered_map<unsigned int, Graphics::Shader::Shader*> m_FragmentShaders;
	std::unordered_map<unsigned int, Graphics::Shader::Shader*> m_GeometryShaders;

	std::unordered_map<std::string, Graphics::Shader::ShaderProgram*> m_Programs;
};

