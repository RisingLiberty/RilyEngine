#include "stdafx.h"

#include "MathHelperMethods.h"

#include "../Components/TransformComponent.h"

#include "../Defines/MathDefines.h"

#include "Graphics/Camera.h"

namespace rlm
{
	float DegreesToRad(float deg)
	{
		return (float)(deg * DegToRad);
	}

	float RadToDegrees(float rad)
	{
		return (float)(rad * RadToDeg);
	}

	Math::Mat44 CalculateTransformMatrix(const Math::Vec3& position)
	{
		return Math::Mat44(
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				position.x, position.y, position.z, 1
			});
	}

	Math::Mat44 CalculateRotationMatrix(const Math::Vec3& rotation)
	{
		Math::Mat33 x = Math::Mat33({
			1,0,0,
			0, cos(rotation.x), -sin(rotation.x),
			0, sin(rotation.x), cos(rotation.x)
			});

		Math::Mat33 y = Math::Mat33({
			cos(rotation.y), 0, sin(rotation.y),
			0,1,0,
			-sin(rotation.y), 0, cos(rotation.y)
			});

		Math::Mat33 z = Math::Mat33({
			cos(rotation.z), -sin(rotation.z), 0,
			sin(rotation.z), cos(rotation.z), 0,
			0,0,1
			});

		Math::Mat33 mat = x * y * z;

		return Math::Mat44({
			mat.m[0][0], mat.m[0][1], mat.m[0][2],	0,
			mat.m[1][0], mat.m[1][1], mat.m[1][2],	0,
			mat.m[2][0], mat.m[2][1], mat.m[2][2],	0,
			0,				0,			0,		1
			});
	}

	Math::Mat44 CalculateScaleMatrix(const Math::Vec3& scale)
	{
		return Math::Mat44({
			scale.x, 0,0,0,
			0, scale.y,0,0,
			0,0,scale.z,0,
			0,0,0,1
			});
	}

	Math::Mat44 CalculateWorldMatrix(const Math::Vec3& position, const Math::Vec3& rotation, const Math::Vec3& scale)
	{
		Math::Mat44 scaleMat = CalculateScaleMatrix(scale);
		Math::Mat44 rotMat = CalculateRotationMatrix(rotation);
		Math::Mat44 transMat = CalculateTransformMatrix(position);

		return scaleMat * rotMat * transMat;
	}

	Math::Mat44 CalculateWorldMatrix(const Math::Transform& transform)
	{
		return CalculateWorldMatrix(transform.Position, transform.Rotation, transform.Scale);
	}

	Math::Mat44 CalculateWorldViewProjection(const Math::Transform& transform, Camera* pCamera)
	{
		Math::Mat44 world = rlm::CalculateWorldMatrix(transform);
		Math::Mat44 view = pCamera->GetViewMatrix();
		Math::Mat44 proj = pCamera->GetProjectionMatrix();

		Math::Mat44 mvp = world * view * proj;

		return mvp;
	}
}
