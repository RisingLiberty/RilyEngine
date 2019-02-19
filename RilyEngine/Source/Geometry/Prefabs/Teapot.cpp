#include "stdafx.h"

#include "TeaPot.h"

#include "Content/Readers/ObjReader.h"

#include "Core/Managers/SystemManager.h"
#include "Core/System/Window.h"

#include "Graphics/Materials/DefaultMaterial.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Camera.h"


namespace Geometry::Prefab
{


Teapot::Teapot(const std::string& name, Component::TransformComponent* pTransform, Graphics::Material::Material* pMaterial):
	PrefabBase(name, pTransform, new Component::MeshFilter(Content::Reader::ObjReader::Read("data/meshes/Teapot.obj"), pMaterial))
{
}

Teapot::~Teapot()
{
}

}
