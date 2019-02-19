#include "stdafx.h"

#include "Scene.h"

#include "SceneObject.h"

#include "Core/Managers/SystemManager.h"

#include "Graphics/Materials/Material.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Rendering/RenderObject.h"

#include "../Components/MeshFilter.h"

namespace Scenegraph
{


Scene::Scene(const std::string& name):
	m_Name(name)
{
}


Scene::~Scene()
{
	std::for_each(m_Objects.begin(), m_Objects.end(),
		[&](auto pair)
	{
		SAFE_DELETE(pair.second);
	});
}

void Scene::Update(float deltaTime)
{
	std::for_each(m_Objects.begin(), m_Objects.end(),
		[&](auto pair)
	{
		pair.second->Update(deltaTime);
	});
}

void Scene::Render()
{
	SystemManager::GetInstance()->GetRenderer()->PreRender();

	std::for_each(m_Objects.begin(), m_Objects.end(),
		[&](auto pair)
	{
		SceneObject* pObject = pair.second;

		if (pObject->ShouldDraw())
		{
			Component::MeshFilter* pMeshFilter = pObject->GetComponent<Component::MeshFilter>(); 
			pMeshFilter->GetMaterial()->Use();
			SystemManager::GetInstance()->GetRenderer()->Submit(new Graphics::Rendering::RenderObject(pMeshFilter, pObject->GetComponent<Component::TransformComponent>()->GetTransform()));
		}
	});

	SystemManager::GetInstance()->GetRenderer()->Render();

	SystemManager::GetInstance()->GetRenderer()->PostRender();

}

void Scene::AddObject(SceneObject* pObject)
{
	m_Objects[pObject->GetID()] = pObject;
}

void Scene::RemoveObject(SceneObject* pObject)
{
	SAFE_DELETE(m_Objects[pObject->GetID()])
}

void Scene::RemoveObject(uint_t id)
{
	SAFE_DELETE(m_Objects[id]);
}

}
