#pragma once

#include "Material.h"

class ShaderProgram;

namespace Graphics::Material
{


class DefaultMaterial final: public Material
{
public:
	DefaultMaterial(Math::Color color = Math::Color::Red);
	DefaultMaterial(const DefaultMaterial& defaultMaterial);

	virtual ~DefaultMaterial();
	virtual Material* Copy() const;

private:
	static const std::string DEFAULT_VERTEXSHADER_PATH;
	static const std::string DEFAULT_FRAGMENTSHADER_PATH;
};

}
