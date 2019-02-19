#pragma once

#include "Math/Transform.h"

class Camera;

namespace rlm
{
	float DegreesToRad(float deg);
	float RadToDegrees(float rad);

	Math::Mat44 CalculateTransformMatrix(const Math::Vec3& position);
	Math::Mat44 CalculateRotationMatrix(const Math::Vec3& rotation);
	Math::Mat44 CalculateScaleMatrix(const Math::Vec3& scale);

	Math::Mat44 CalculateWorldMatrix(const Math::Vec3& position, const Math::Vec3& rotation, const Math::Vec3& scale);
	Math::Mat44 CalculateWorldMatrix(const Math::Transform& transform);

	Math::Mat44 CalculateWorldViewProjection(const Math::Transform& transform, Camera* pCamera);
}