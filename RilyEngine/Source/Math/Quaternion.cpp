#include "stdafx.h"

#include "Quaternion.h"

namespace Math
{


Quaternion::Quaternion() :
	Vec(ZeroVec3),
	Scalar(1)
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float angle):
	Quaternion(Vec3(_x, _y, _z), angle)
{
	
}

Quaternion::Quaternion(const Vec3& axis, float angle):
	Vec(axis * sin(angle*0.5f)),
	Scalar(cos(angle*0.5f))
{
}

Quaternion::Quaternion(const Quaternion& quat):
	Vec(quat.Vec),
	Scalar(quat.Scalar)
{
}

Quaternion::Quaternion(const Math::Mat33& mat)
{
	float trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
	float s, w, x, y, z = 0;


	if (trace > 0)
	{
		s = 0.5f / sqrt(trace);
		w = 0.25f / s;
		x = (mat.m[2][1] - mat.m[1][2]) * s;
		y = (mat.m[0][2] - mat.m[2][0]) * s;
		z = (mat.m[1][0] - mat.m[0][1]) * s;
	}
	else if ((mat.m[0][0] > mat.m[1][1])&&mat.m[0][0] > mat.m[2][2])
	{
		s = sqrt(1.0f + mat.m[0][0] - mat.m[1][1] - mat.m[2][2]) * 2;
		w = (mat.m[2][1] - mat.m[1][2]) / s;
		x = 0.25f * s;
		y = (mat.m[0][1] + mat.m[1][0]) / s;
		z = (mat.m[0][0] + mat.m[2][0]) / s;
	}
	else if (mat.m[1][1] > mat.m[2][2])
	{
		s = sqrt(1.0f + mat.m[1][1] - mat.m[0][0] - mat.m[2][2]) * 2;
		w = (mat.m[0][2] - mat.m[2][0]) / s;
		x = (mat.m[0][1] + mat.m[1][0]) / s;
		y = 0.25f * s;
		z = (mat.m[1][2] + mat.m[2][1]) / s;
	}
	else
	{
		s = sqrt(1.0f + mat.m[2][2] - mat.m[0][0] - mat.m[1][1]) * 2;
		w = (mat.m[1][0] - mat.m[0][1]) / s;
		x = (mat.m[0][2] + mat.m[2][0]) / s;
		z = 0.25f * s;
	}

	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion& Quaternion::operator=(const Quaternion& quat)
{
	Vec = quat.Vec;
	Scalar = quat.Scalar;
	return *this;
}


Quaternion::~Quaternion()
{
}

Quaternion Quaternion::operator+(const Quaternion& quat) const 
{
	return Quaternion(Vec + quat.Vec, w + quat.w);
}

Quaternion Quaternion::operator+=(const Quaternion& quat)
{
	*this = *this + quat;
	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
	return Quaternion(Vec - quat.Vec, Scalar - quat.Scalar);
}

Quaternion Quaternion::operator-=(const Quaternion& quat)
{
	*this = *this - quat;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
{
	return Quaternion(
		(((w * quat.x) + (x * quat.w)) + (y * quat.z)) - (z * quat.y),
		(((w * quat.y) + (y * quat.w)) + (z * quat.x)) - (x * quat.z),
		(((w * quat.z) + (z * quat.w)) + (x * quat.y)) - (y * quat.x),
		(((w * quat.w) - (x * quat.x)) - (y * quat.y)) - (z * quat.z)
	).GetNormalized();
}

Quaternion Quaternion::operator*=(const Quaternion& quat)
{
	*this = *this * quat;
	return *this;
}

Quaternion Quaternion::operator*(float scalar) const
{
	return Quaternion(Vec * scalar, Scalar * scalar);
}

Quaternion Quaternion::operator*=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

Quaternion Quaternion::operator/(const Quaternion& quat) const
{
	return *this * quat.GetInverse();
}

Quaternion Quaternion::operator/=(const Quaternion& quat)
{
	*this = *this / quat;
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-Vec, -Scalar);
}

bool Quaternion::operator==(const Quaternion& quat) const
{
	return Scalar == quat.Scalar && Vec == quat.Vec;
}

bool Quaternion::operator!=(const Quaternion& quat) const
{
	return !(*this == quat);
}

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-Vec, Scalar);
}

Quaternion Quaternion::GetNormalized() const
{
	float norm = Norm();

	if (norm == 0)
	{
		Debug::Log(Debug::LogType::WARNING, "Null Quaternion");
		return Quaternion(ZeroVec3, 0);
	}

	float lenInv = 1 / sqrt(norm);
	return Quaternion(Vec, Scalar) * lenInv;
}

Quaternion Quaternion::GetInverse() const
{
	return this->GetConjugate() * (1 / Norm());
}

Quaternion Quaternion::GetUnitQuaternion() const
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

//roll
float Quaternion::GetXAngle() const
{
	float sin = 2 * (w * x + y * z);
	float cos = 1 - 2 * (x * x + y * y);
	return atan2(sin, cos);
}

//pitch
float Quaternion::GetYAngle() const
{
	float sin = 2 * (w * y - z * x);
	if (fabs(sin) >= 1)
		return copysign((float)RL_PI_DIV_2, sin); // use 90 degrees if out of range
	else
		return asin(sin);
}

//yaw
float Quaternion::GetZAngle() const
{
	float sin = 2 * (w * z + x * y);
	float cos = 1 - 2 * (y * y + z * z);
	return atan2(sin, cos);
}

Vec3 Quaternion::GetEulerAngles() const
{
	return Vec3(atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		asin(2 * x * y + 2 * z * w));
}

void Quaternion::SetEulerAngles(const Vec3& angles)
{
	Quaternion pitch(Vec3(1.0, 0.0, 0.0), angles.x);
	Quaternion yaw(Vec3(0.0, 1.0, 0.0), angles.y);
	Quaternion roll(Vec3(0.0, 0.0, 1.0), angles.z);
	*this = pitch * yaw * roll;
}

Vec3 Quaternion::Rotate(const Quaternion& quat, const Vec3& vec)
{
	float tmpX, tmpY, tmpZ, tmpW;
	tmpX = (((quat.w * vec.x) + (quat.y * vec.z)) - (quat.z * vec.y));
	tmpY = (((quat.w * vec.y) + (quat.z * vec.x)) - (quat.x * vec.z));
	tmpZ = (((quat.w * vec.z) + (quat.x * vec.y)) - (quat.y * vec.x));
	tmpW = (((quat.x * vec.x) + (quat.y * vec.y)) + (quat.z * vec.z));
	return Vec3(
		((((tmpW * quat.x) + (tmpX * quat.w)) - (tmpY * quat.z)) + (tmpZ * quat.y)),
		((((tmpW * quat.y) + (tmpY * quat.w)) - (tmpZ * quat.x)) + (tmpX * quat.z)),
		((((tmpW * quat.z) + (tmpZ * quat.w)) - (tmpX * quat.y)) + (tmpY * quat.x))
	);
}

float Quaternion::Norm() const
{
	return w * w + x * x + y * y + z * z;
}

void Quaternion::Conjugate()
{
	*this = this->GetConjugate();
}

void Quaternion::Normalize()
{
	*this = this->GetNormalized();
}

void Quaternion::Inverse()
{
	*this = this->GetInverse();
}

Vec3 Quaternion::RotatePoint(const Vec3& point) const
{
	Quaternion qv = Quaternion(point, 0);
	Quaternion qm = *this * qv * this->GetInverse();

	return qm.Vec;
}

Math::Mat33 Quaternion::ToMatrix() const
{
	return Math::Mat33(
		{
			1-2*(y*y),		2*x*y - 2*z*w,			2*x*z + 2*y*w,
			2*x*y + 2*z*w,	1-2*(x*x) - 2*(x*x),	2*y*z - 2*x*w,
			2*x*z - 2*y*w,	2*y*z + 2*x*w,			1-2*(x*x) - 2*(y*y)
		});
}

Quaternion Quaternion::RotationX(float angle)
{
	angle *= 0.5f;
	return Quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
}

Quaternion Quaternion::RotationY(float angle)
{
	angle *= 0.5f;
	return Quaternion(0.0f, sin(angle), 0.0f, cos(angle));

}

Quaternion Quaternion::RotationZ(float angle)
{
	angle *= 0.5f;
	return Quaternion(0.0f, 0.0f, sin(angle), cos(angle));

}

}
