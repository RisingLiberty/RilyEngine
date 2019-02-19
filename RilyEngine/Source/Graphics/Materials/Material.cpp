#include "stdafx.h"

#include "Material.h"

#include "MaterialParameter.h"

#include "Core/Managers/ResourceManager.h"

#include "Graphics/Shaders/ShaderBuilder.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/Uniform.h"


namespace Graphics::Material
{


	Material::Material(Graphics::Shader::ShaderProgram* pProgram) :
		m_pProgram(pProgram)
	{
	}

	Material::Material(const Material& material) :
		m_pProgram(new Graphics::Shader::ShaderProgram(*material.m_pProgram))
	{
	}

	Material::~Material()
	{
		m_Parameters.DeleteAllPointers();
	}

	//Scans the shader for all it's uniforms
	//and creates parameters for these uniforms
	int Material::Initialize()
	{
		Container::Vector<Graphics::Shader::Uniform> uniforms = m_pProgram->GetUniforms();

		for (Graphics::Shader::Uniform& uniform : uniforms)
		{
			switch (uniform.Type)
			{
			case Graphics::Shader::UniformDataType::INT:
				this->AddParameter(new MaterialParameter<int>(uniform.Name, 0, std::bind(&Graphics::Shader::ShaderProgram::SetUniform<int>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::FLOAT:
				this->AddParameter(new MaterialParameter<float>(uniform.Name, 0.0f, std::bind(&Graphics::Shader::ShaderProgram::SetUniform<float>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::VEC2:
				this->AddParameter(new MaterialParameter<Math::Vec2>(uniform.Name, ZeroVec2, std::bind(&Graphics::Shader::ShaderProgram::SetUniform<Math::Vec2>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::VEC3:
				this->AddParameter(new MaterialParameter<Math::Vec3>(uniform.Name, ZeroVec3, std::bind(&Graphics::Shader::ShaderProgram::SetUniform<Math::Vec3>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::VEC4:
				this->AddParameter(new MaterialParameter<Math::Vec4>(uniform.Name, ZeroVec4, std::bind(&Graphics::Shader::ShaderProgram::SetUniform<Math::Vec4>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::MAT33:
				this->AddParameter(new MaterialParameter<Math::Mat33>(uniform.Name, Math::Mat33(), std::bind(&Graphics::Shader::ShaderProgram::SetUniform<Math::Mat33>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			case Graphics::Shader::UniformDataType::MAT44:
				this->AddParameter(new MaterialParameter<Math::Mat44>(uniform.Name, Math::Mat44(), std::bind(&Graphics::Shader::ShaderProgram::SetUniform<Math::Mat44>, m_pProgram, std::placeholders::_1, std::placeholders::_2)));
				break;
			}
		}

		return OK;
	}

	void Material::Use()
	{
		m_pProgram->Bind();
		this->UpdateShaderVariables();
	}

	void Material::UpdateShaderVariables()
	{
		//to update certain parameters before they get send to the shader
		for (std::function<void()> updateMethod : m_UpdateMethods)
			updateMethod();

		//send parameters to shader
		for (MaterialParameterBase* pParameter : m_Parameters)
			pParameter->SendToShader();
	}

}
