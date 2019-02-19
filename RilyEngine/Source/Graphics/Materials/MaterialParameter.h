#pragma once

namespace Graphics::Material
{

	class Material;

	class MaterialParameterBase
	{
	public:
		MaterialParameterBase(const std::string& name) :
			m_Name(name)
		{
		}
		virtual ~MaterialParameterBase() = default;
		virtual void SendToShader() const = 0;

		std::string GetName() const { return m_Name; }

	protected:
		std::string m_Name;

	};

	template <typename T>
	class MaterialParameter : public MaterialParameterBase
	{
	public:
		MaterialParameter(const std::string& name, T data, std::function<void(const std::string&, T)> updateFunction) :
			MaterialParameterBase(name),
			m_Data(data),
			m_UpdateFunction(updateFunction)
		{
		}

		T GetData() const { return m_Data; };
		void SetData(T data) { m_Data = data; }

		void SendToShader() const override
		{
			m_UpdateFunction(m_Name, m_Data);
		}

	protected:
		T m_Data;
		std::function<void(const std::string&, T)> m_UpdateFunction;
	};

}