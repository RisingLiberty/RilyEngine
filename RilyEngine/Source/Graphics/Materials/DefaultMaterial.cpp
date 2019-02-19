#include "stdafx.h"

#include "DefaultMaterial.h"

#include "MaterialParameter.h"

#include "Core/Managers/ShaderManager.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/ShaderBuilder.h"

namespace Graphics::Material
{
	const std::string DefaultMaterial::DEFAULT_VERTEXSHADER_PATH = SHADER_PATH + "DefaultShader.vertex";
	const std::string DefaultMaterial::DEFAULT_FRAGMENTSHADER_PATH = SHADER_PATH + "DefaultShader.fragment";

	DefaultMaterial::DefaultMaterial(Math::Color color) :
		Material(ShaderManager::GetInstance()->GetShader("DefaultShaderProgram"))
	{
		Material::Initialize();
		this->UpdateVariable("u_color", color);
	}

	DefaultMaterial::DefaultMaterial(const DefaultMaterial& defaultMaterial) :
		Material(ShaderManager::GetInstance()->GetShader("DefaultShaderProgram"))
	{
		Material::Initialize();
		Math::Color color = defaultMaterial.GetVariableValue<Math::Color>("u_color");
		this->UpdateVariable("u_color", color);
	}

	DefaultMaterial::~DefaultMaterial()
	{
	}

	Material* DefaultMaterial::Copy() const
	{
		Math::Color color = this->GetVariableValue<Math::Color>("u_color");
		Material* pMaterial = new DefaultMaterial(color);
		return pMaterial;
	}
}
