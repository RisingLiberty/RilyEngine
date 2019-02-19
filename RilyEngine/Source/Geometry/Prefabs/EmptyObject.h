#pragma once

#include "PrefabBase.h"

namespace Geometry::Prefab
{
	class EmptyObject : public PrefabBase
	{
	public:
		EmptyObject(const std::string& name, Component::TransformComponent* pTransform);
		virtual ~EmptyObject();
	};
}
