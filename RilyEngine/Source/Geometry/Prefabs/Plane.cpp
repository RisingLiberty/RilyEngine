#include "stdafx.h"

#include "Plane.h"

#include "Components/TransformComponent.h"
#include "Components/MeshFilter.h"

#include "Content/Readers/ObjReader.h"

#include "Core/Managers/SystemManager.h"
#include "Core/System/Window.h"

#include "Graphics/Materials/DefaultMaterial.h"
#include "Graphics/Materials/Material.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Vertex/Vertex.h"
#include "Graphics/Vertex/VertexAttribute.h"
#include "Graphics/Vertex/VertexFactory.h"
#include "Graphics/Camera.h"


namespace Geometry::Prefab
{
	Plane::Plane(const std::string& name, Component::TransformComponent* pTransform, Graphics::Material::Material* pMaterial) :
		PrefabBase(name, pTransform, new Component::MeshFilter(Content::Reader::ObjReader::Read("Data/meshes/plane.obj"), pMaterial))
	{
	}


	Plane::~Plane()
	{
	}

	int Plane::Initialize()
	{
		return OK;
	}

	Plane* Plane::Copy() const
	{
		Component::TransformComponent* pTransform = new Component::TransformComponent(*m_pTransform);
		Graphics::Material::Material* pMat = new Graphics::Material::DefaultMaterial();
		Graphics::Material::Material* pMaterial = m_pMesh->GetMaterial()->Copy();

		//std::function<void()> f = std::bind(UpdateDefaultMaterial, m_pTransform, m_pMesh->GetMaterial());
		//void(*func)(Component::Transform*, Graphics::Material::Material*) = UpdateDefaultMaterial;

		Plane* pPlane = new Plane(m_Name + "_Copy", pTransform, pMaterial);
		return pPlane;
	}
}
