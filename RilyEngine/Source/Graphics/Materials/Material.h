#pragma once

#include "MaterialParameter.h"
#include "../Shaders/ShaderProgram.h"
#include "MaterialParameter.h"

#include "Math/Transform.h"

namespace Graphics::Material
{
	class Material
	{
	public:
		Material(Graphics::Shader::ShaderProgram* pProgram);
		Material(const Material& material);
		virtual ~Material();

		virtual int Initialize();
		void Use();
		virtual Material* Copy() const = 0;

		void AddParameter(MaterialParameterBase* parameter)
		{
			m_Parameters.AddC(parameter);
		}

		void AddUpdateMethod(std::function<void()> updateMethod)
		{
			m_UpdateMethods.AddC(updateMethod);
		}

		template <typename T>
		void UpdateVariable(const std::string& name, T value)
		{
			auto it = std::find_if(m_Parameters.CBegin(), m_Parameters.CEnd(),
				[&](MaterialParameterBase* parameter)
			{
				return parameter->GetName() == name;
			});

			if (it == m_Parameters.CEnd())
			{
				Debug::Log(Debug::LogType::ERROR, "Unable to find parameter");
				return;
			}

			dynamic_cast<MaterialParameter<T>*>(*it)->SetData(value);
		}

		template <typename T>
		T GetVariableValue(const std::string& name) const
		{
			auto it = std::find_if(m_Parameters.CBegin(), m_Parameters.CEnd(),
				[&](MaterialParameterBase* parameter)
			{
				return parameter->GetName() == name;
			});

			if (it == m_Parameters.CEnd())
			{
				Debug::Log(Debug::LogType::ERROR, "Unable to find paramter");
				return T();
			}

			return dynamic_cast<MaterialParameter<T>*>(*it)->GetData();
		}

		void UpdateShaderVariables();

	protected:

	protected:
		Graphics::Shader::ShaderProgram* m_pProgram;
		Container::Vector<std::function<void()>> m_UpdateMethods;
		Container::Vector<MaterialParameterBase*> m_Parameters;
	};

}
