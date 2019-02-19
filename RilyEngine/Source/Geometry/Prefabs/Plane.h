#pragma once

#include "PrefabBase.h"

namespace Graphics::Material
{
	class Material;
}

namespace Geometry::Prefab
{


class Plane : public PrefabBase
{
public:
	Plane(const std::string& name, Component::TransformComponent* pTransform, Graphics::Material::Material* pMaterial = nullptr);
	~Plane();

	int Initialize() override;

	Plane* Copy() const;

private:
};

}
