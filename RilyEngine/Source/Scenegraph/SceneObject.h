#pragma once

class Scene;
#include "../Components/TransformComponent.h"

namespace Scenegraph
{


class SceneObject
{
public:
	SceneObject(const std::string& name, Component::TransformComponent* pTransform);
	virtual ~SceneObject();

	virtual int Initialize();
	virtual void Update(float deltaTime);
	
	bool ShouldDraw();
	uint_t GetID() const { return m_ID; }

	Component::TransformComponent* GetTransform() const { return m_pTransform; }
	void SetTransform(Component::TransformComponent* pTransform) { m_pTransform = pTransform; }

	void Translate(const Math::Vec3& vec);
	void Rotate(const Math::Vec3& vec, float angle);
	void Scale(const Math::Vec3& scale) ;

	Math::Vec3 GetFoward() const;
	Math::Vec3 GetRight() const;
	Math::Vec3 GetUp() const;
	Math::Vec3 GetLeft() const;
	Math::Vec3 GetBack() const;
	Math::Vec3 GetDown() const;

	Math::Quaternion GetOrientation() const;

	void SetPosition(const Math::Vec3& position) { m_pTransform->SetPosition(position); }
	void SetRotation(const Math::Vec3& rotation) { m_pTransform->SetRotation(rotation); }
	void SetScale(const Math::Vec3& scale) { m_pTransform->SetScale(scale); }

	template <typename T>
	T* GetComponent()
	{
		auto it = std::find_if(m_Components.Begin(), m_Components.End(),
			[&](Component::ComponentBase* pComponent)
		{
			return dynamic_cast<T*>(pComponent);
		});

		if (it != m_Components.End())
			return dynamic_cast<T*>(*it);

		return nullptr;
	}

	Component::ComponentBase* GetComponent(uint_t index);

protected:
	Component::TransformComponent* m_pTransform = nullptr;
	std::string m_Name;
	uint_t m_ID;
	static uint_t s_CurrentID;

	Container::Vector<Component::ComponentBase*> m_Components;
};

}
