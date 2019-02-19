#include "stdafx.h"

#include "ShaderBuilder.h"

#include "Shader.h"
#include "ShaderProgram.h"

#include "../../Core/Managers/ShaderManager.h"

#include "../../Resources/Shaders/ShaderSource.h"

namespace Graphics::Shader
{

Shader* ShaderBuilder::BuildShader(const Resources::ShaderSource* pSource)
{
	Shader* pShader = new Shader();
	pShader->Compile(pSource);

	switch (pSource->GetType())
	{
	case GL_VERTEX_SHADER:	
		if (!ShaderManager::GetInstance()->BindVertexShader(pShader, pSource))
		{
			delete pShader;
			return ShaderManager::GetInstance()->GetVertexShader(pSource->GetCode());
		}
		break;
	case GL_GEOMETRY_SHADER: 
		if (!ShaderManager::GetInstance()->BindGeometryShader(pShader, pSource))
		{
			delete pShader;
			return ShaderManager::GetInstance()->GetGeometryShader(pSource->GetCode());
		}
		break;
	case GL_FRAGMENT_SHADER: 
		if (!ShaderManager::GetInstance()->BindFragmentShader(pShader, pSource))
		{
			delete pShader;
			return ShaderManager::GetInstance()->GetFragmentShader(pSource->GetCode());
		}
		break;
	default: Debug::Log(Debug::LogType::WARNING, "Wrong shadertype");  break;
	}

	return pShader;
}

ShaderProgram* ShaderBuilder::CreateShaderProgram(const Container::Vector<unsigned int>& shaderIDs, const std::string& name)
{
	ShaderProgram* pShaderProgram = new ShaderProgram(name);
	pShaderProgram->Create(shaderIDs);

	if (!ShaderManager::GetInstance()->AddProgram(pShaderProgram))
	{
		delete pShaderProgram;
		pShaderProgram = ShaderManager::GetInstance()->GetShader(name);
	}

	for (unsigned int id : shaderIDs)
	{
		GLCall(glDetachShader(pShaderProgram->GetID(), id));
		GLCall(glDeleteShader(id));
	}

	return pShaderProgram;
}

}