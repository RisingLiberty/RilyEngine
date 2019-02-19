#pragma once

#include "../../Components/Components.h"
#include "../../Scenegraph/SceneObject.h"

namespace Graphics::Material
{
	class Material;
}

namespace Geometry::Prefab
{


class PrefabBase : public Scenegraph::SceneObject
{
public:
	PrefabBase(const std::string& name, Component::TransformComponent* pTransform, Component::MeshFilter* pMesh = nullptr);
	virtual ~PrefabBase();

	virtual int Initialize() override { return OK; };
	virtual void Update(float deltaTime) override;

	void SetMesh(Component::MeshFilter* pMesh);
	Component::MeshFilter* GetMesh() const { return m_pMesh; }
protected:
	Component::MeshFilter* m_pMesh = nullptr;
};

}
