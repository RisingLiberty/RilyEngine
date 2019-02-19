#include "stdafx.h"

#include "ShaderManager.h"

#include "ResourceManager.h"

#include "Resources/Shaders/ShaderSource.h"

#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderBuilder.h"
#include "Graphics/Shaders/ShaderProgram.h"

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
	std::for_each(m_VertexShaders.begin(), m_VertexShaders.end(),
		[&](auto pair)
	{
		delete pair.second;
	});

	std::for_each(m_GeometryShaders.begin(), m_GeometryShaders.end(),
		[&](auto pair)
	{
		delete pair.second;
	});

	std::for_each(m_FragmentShaders.begin(), m_FragmentShaders.end(),
		[&](auto pair)
	{
		delete pair.second;
	});

	std::for_each(m_Programs.begin(), m_Programs.end(),
		[&](auto pair)
	{
		delete pair.second;
	});
}

int ShaderManager::Initialize()
{
	Resources::ShaderSource* pDefaultVertexSource = dynamic_cast<Resources::ShaderSource*>(ResourceManager::GetInstance()->LoadShaderSource("DefaultShader.vertex", Resources::ShaderType::VERTEX));
	Resources::ShaderSource* pDefaultFragmentSource = dynamic_cast<Resources::ShaderSource*>(ResourceManager::GetInstance()->LoadShaderSource("DefaultShader.fragment", Resources::ShaderType::FRAGMENT));

	Graphics::Shader::Shader* pVertexShader = Graphics::Shader::ShaderBuilder::BuildShader(pDefaultVertexSource);
	Graphics::Shader::Shader* pFragmentShader = Graphics::Shader::ShaderBuilder::BuildShader(pDefaultFragmentSource);

	delete pDefaultVertexSource;
	delete pDefaultFragmentSource;

	Container::Vector<unsigned int> vec = { pVertexShader->GetID(), pFragmentShader->GetID() };
	Graphics::Shader::ShaderProgram* pProgram = Graphics::Shader::ShaderBuilder::CreateShaderProgram(vec, "DefaultShaderProgram");

	m_Programs["DefaultShaderProgram"] = pProgram;

	return OK;
}

bool ShaderManager::BindVertexShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource)
{
	uint_t codeHash = std::hash<std::string>()(pSource->GetCode());

	auto it = m_VertexShaders.find(codeHash);
	
	if (it != m_VertexShaders.end())
	{
		Debug::Log(Debug::LogType::WARNING, "Vertex shader already exists");
		return false;
	}

	m_VertexShaders[codeHash] = pShader;
	return true;
}

bool ShaderManager::BindGeometryShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource)
{
	uint_t codeHash = std::hash<std::string>()(pSource->GetCode());

	auto it = m_GeometryShaders.find(codeHash);

	if (it != m_GeometryShaders.end())
	{
		Debug::Log(Debug::LogType::WARNING, "Vertex shader already exists");
		return false;
	}

	m_GeometryShaders[codeHash] = pShader;
	return true;
}

bool ShaderManager::BindFragmentShader(Graphics::Shader::Shader* pShader, const Resources::ShaderSource* pSource)
{
	uint_t codeHash = std::hash<std::string>()(pSource->GetCode());

	auto it = m_FragmentShaders.find(codeHash);

	if (it != m_FragmentShaders.end())
	{
		Debug::Log(Debug::LogType::WARNING, "Vertex shader already exists");
		return false;
	}

	m_FragmentShaders[codeHash] = pShader;
	return true;
}

bool ShaderManager::AddProgram(Graphics::Shader::ShaderProgram* pProgram)
{
	auto it = m_Programs.find(pProgram->GetName());

	if (it != m_Programs.end())
	{
		Debug::Log(Debug::LogType::WARNING, "Program with same name already exists");
		return false;
	}

	m_Programs[pProgram->GetName()] = pProgram;
	return true;
}

Graphics::Shader::Shader* ShaderManager::GetVertexShader(const std::string& code) const
{
	auto it = m_VertexShaders.find(std::hash<std::string>()(code));

	if (it == m_VertexShaders.end())
		return nullptr;

	return it->second;
}

Graphics::Shader::Shader* ShaderManager::GetGeometryShader(const std::string& code) const
{
	auto it = m_GeometryShaders.find(std::hash<std::string>()(code));

	if (it == m_GeometryShaders.end())
		return nullptr;

	return it->second;
}

Graphics::Shader::Shader* ShaderManager::GetFragmentShader(const std::string& code) const
{
	auto it = m_FragmentShaders.find(std::hash<std::string>()(code));

	if (it == m_FragmentShaders.end())
		return nullptr;

	return it->second;
}

Graphics::Shader::ShaderProgram* ShaderManager::GetShader(const std::string& name) const
{
	auto it = m_Programs.find(name);

	if (it == m_Programs.end())
		return nullptr;

	return it->second;
}