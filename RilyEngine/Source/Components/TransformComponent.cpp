#include "stdafx.h"

#include "TransformComponent.h"

namespace Component
{

	TransformComponent::TransformComponent(const Math::Vec3& position, const Math::Vec3& rotation, const Math::Vec3& scale) :
		m_Transform(Math::Transform(position,rotation, scale))
	{
	}

	TransformComponent::TransformComponent(const Math::Transform& transform) :
		m_Transform(transform)
	{

	}

	TransformComponent::TransformComponent(const TransformComponent& transform) :
		m_Transform(Math::Transform(transform.m_Transform.Position, transform.m_Transform.Rotation, transform.m_Transform.Scale))
	{

	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::Translate(const Math::Vec3& translation)
	{
		m_Transform.Position += translation;
	}

	void TransformComponent::Rotate(const Math::Vec3& rotation)
	{
		m_Transform.Rotation += rotation;
	}

	void TransformComponent::Scale(const Math::Vec3& scale)
	{
		m_Transform.Scale += scale;
	}

}

