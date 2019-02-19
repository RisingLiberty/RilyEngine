#include "stdafx.h"

#include "EmptyObject.h"

namespace Geometry::Prefab
{
	EmptyObject::EmptyObject(const std::string& name, Component::TransformComponent* pTransform):
		PrefabBase(name, pTransform)
	{

	}

	EmptyObject::~EmptyObject()
	{
	}
}