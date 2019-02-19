#pragma once

namespace Math
{
	struct Transform
	{
		Transform(Vec3 position, Vec3 rotation, Vec3 scale);

		Vec3 Position;
		Vec3 Rotation;
		Vec3 Scale;
	};

	std::ostream& operator<<(std::ostream& os, const Transform& transform);

#define UnitTransform Transform(ZeroVec3, ZeroVec3, Math::Vec3(1.0f, 1.0f, 1.0f))
}