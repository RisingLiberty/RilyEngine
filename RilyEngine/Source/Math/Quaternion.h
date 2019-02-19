#pragma once

//all prace the goldy formula:
//i^2 == j^2 == k^2 == ijk == -1


/*
	  	 i	 j	k 
	  +----+----+----+
	i | -1 | k  | -j |
	  +--------------+
	j |	-k | -1 |  i |
	  +--------------+
	k |	 j | -i | -1 |
	  +--------------+
*/


namespace Math
{


struct Quaternion
{
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float angle);
	Quaternion(const Vec3& axis, float angle);
	Quaternion(const Quaternion& quat);
	Quaternion(const Math::Mat33& mat);

	Quaternion& operator=(const Quaternion& quat);

	~Quaternion();

	Quaternion operator+(const Quaternion& quat) const;
	Quaternion operator+=(const Quaternion& quat);
	Quaternion operator-(const Quaternion& quat) const;
	Quaternion operator-=(const Quaternion& quat);
	Quaternion operator*(const Quaternion& quat) const;
	Quaternion operator*=(const Quaternion& quat);
	Quaternion operator*(float scalar) const;
	Quaternion operator*=(float scalar);
	Quaternion operator/(const Quaternion& quat) const;
	Quaternion operator/=(const Quaternion& quat);

	Quaternion operator-() const;

	bool operator==(const Quaternion& quat) const;
	bool operator!=(const Quaternion& quat) const;

	Quaternion GetConjugate() const;
	Quaternion GetNormalized() const;
	Quaternion GetInverse() const;
	Quaternion GetUnitQuaternion() const;

	float GetXAngle() const;
	float GetYAngle() const;
	float GetZAngle() const;

	Vec3 GetEulerAngles() const;
	void SetEulerAngles(const Vec3& angles);
	static Vec3 Rotate(const Quaternion& quat, const Vec3& vec);

	float Norm() const;

	void Conjugate();
	void Normalize();
	void Inverse();

	Vec3 RotatePoint(const Vec3& point) const;

	Math::Mat33 ToMatrix() const;

	static Quaternion RotationX(float angle);
	static Quaternion RotationY(float angle);
	static Quaternion RotationZ(float angle);

public:
	union
	{
		struct
		{
			float x, y, z, w;
		};

		struct
		{
			Vec3 Vec;
			float Scalar;
		};

	};
};

#define ZeroQuat ::Quaternion()

}
