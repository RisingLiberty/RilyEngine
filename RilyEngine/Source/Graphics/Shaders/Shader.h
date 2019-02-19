#pragma once

namespace Resources
{
	class ShaderSource;
}

namespace Graphics::Shader
{


class Shader
{
public:
	Shader();
	~Shader();

	int Compile(const Resources::ShaderSource* pSource);

	unsigned int GetID() const { return m_ID; }

private:
private:
	unsigned int m_ID;
};
}