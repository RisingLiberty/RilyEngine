#include "stdafx.h"

#include "Transform.h"


namespace Math
{
	Transform::Transform(Vec3 position, Vec3 rotation, Vec3 scale) :
		Position(position),
		Rotation(rotation),
		Scale(scale)
	{

	}

	std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		//Time stamp is displayed by logger

		os << "--Transform--\n";
		os << "Position: " << transform.Position << "\n";
		os << "Rotation: " << transform.Rotation << "\n";
		os << "Scale: " << transform.Scale << "\n";

		return os;
	}

}
