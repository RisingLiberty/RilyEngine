#include "stdafx.h"

#include "PrefabBase.h"

#include "Components/MeshFilter.h"

#include "Core/Managers/SystemManager.h"
#include "Core/System/Window.h"

#include "Graphics/Materials/Material.h"
#include "Graphics/Materials/MaterialParameter.h"
#include "Graphics/Materials/PredefinedParameterNames.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Camera.h"

namespace Geometry::Prefab
{
	PrefabBase::PrefabBase(const std::string& name, Component::TransformComponent* pTransform, Component::MeshFilter* pMesh) :
		SceneObject(name, pTransform),
		m_pMesh(pMesh)
	{
		if (m_pMesh)
		{
			m_Components.AddC(m_pMesh);

			//update prefabs mvp matrix in shader
			m_pMesh->GetMaterial()->AddUpdateMethod([&]()
			{
				Camera* pCamera = SystemManager::GetInstance()->GetWindow()->GetCamera();
				Math::Mat44 mvp = rlm::CalculateWorldViewProjection(m_pTransform->GetTransform(), pCamera);
				m_pMesh->GetMaterial()->UpdateVariable(Graphics::Material::PPN::Mvp, mvp);
			});
		}

	}


	PrefabBase::~PrefabBase()
	{
		delete m_pMesh;
	}

	void PrefabBase::Update(float deltaTime)
	{
	}

	void PrefabBase::SetMesh(Component::MeshFilter* pMesh)
	{
		if (m_pMesh)
			delete m_pMesh;

		if (pMesh)
		{
			m_pMesh = pMesh;
			m_Components.AddC(m_pMesh);

			//update prefabs mvp matrix in shader
			m_pMesh->GetMaterial()->AddUpdateMethod([&]()
			{
				Camera* pCamera = SystemManager::GetInstance()->GetWindow()->GetCamera();
				Math::Mat44 mvp = rlm::CalculateWorldViewProjection(m_pTransform->GetTransform(), pCamera);
				if (m_pMesh->GetMaterial())
					m_pMesh->GetMaterial()->UpdateVariable(Graphics::Material::PPN::Mvp, mvp);
			});

		}
	}
}