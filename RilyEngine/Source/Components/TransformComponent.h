#pragma once

#include "ComponentBase.h"
#include "Math/Transform.h"

namespace Component
{
	class TransformComponent : public ComponentBase
{
public:
	TransformComponent(const Math::Vec3& position, const Math::Vec3& rotation, const Math::Vec3& scale);
	TransformComponent(const Math::Transform& transform);
	TransformComponent(const TransformComponent& transform);
	~TransformComponent();

	void Translate(const Math::Vec3& translation);
	void Rotate(const Math::Vec3& rotation);
	void Scale(const Math::Vec3& scale);

	void SetPosition(const Math::Vec3& position) { m_Transform.Position = position; }
	void SetRotation(const Math::Vec3& rotation) { m_Transform.Rotation = rotation; }
	void SetScale(const Math::Vec3& scale) { m_Transform.Scale = scale; }

	Math::Vec3 GetPosition() const { return m_Transform.Position; }
	Math::Vec3 GetRotation() const { return m_Transform.Rotation; }
	Math::Vec3 GetScale() const { return m_Transform.Scale; }

	Math::Transform GetTransform() const { return m_Transform; }

private:
	Math::Transform m_Transform;
	
};

#define UnitTransformComponent TransformComponent(Math::UnitTransform)
}

