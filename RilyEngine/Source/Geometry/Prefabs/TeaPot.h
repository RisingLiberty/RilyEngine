#pragma once

#include "PrefabBase.h"

namespace Graphics::Material
{
	class Material;
}

namespace Geometry::Prefab
{


class Teapot: public PrefabBase
{
public:
	Teapot(const std::string& name, Component::TransformComponent* pTransform, Graphics::Material::Material* pMaterial);
	~Teapot();


private:
};

}
