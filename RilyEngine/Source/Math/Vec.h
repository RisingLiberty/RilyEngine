#pragma once

namespace Math
{


//Math::Vector 2 struct
//----------------------------------------------
struct Vec2
{
	Math::Vec2(float _x = 0, float _y = 0);
	Math::Vec2(const Math::Vec2& vec);
	Math::Vec2(const Math::Vec2&& vec);

	bool operator==(const Math::Vec2& vec) const;
	bool operator!=(const Math::Vec2& vec) const;

	Math::Vec2& operator=(const Math::Vec2& vec);
	Math::Vec2& operator=(const Math::Vec2&& vec);
	Math::Vec2 operator-() const;
	Math::Vec2 operator-(const Math::Vec2& vec) const;
	Math::Vec2 operator-=(const Math::Vec2& vec);
	Math::Vec2 operator+(const Math::Vec2& vec) const;
	Math::Vec2 operator+=(const Math::Vec2& vec);
	Math::Vec2 operator*(const float scalar) const;
	Math::Vec2 operator*=(const float scalar);
	Math::Vec2 operator/(const float scalar) const;
	Math::Vec2 operator/=(const float scalar);
	Math::Vec2 GetClamped(const float max) const;
	Math::Vec2 GetRightHand() const;
	Math::Vec2 GetLeftHand() const;
	Math::Vec2 GetNormalized() const;

	void Clamp(const float max);
	void Normalize();

	float Dot(const Math::Vec2& vec) const;
	float Magnitude() const;
	float MagnitudeSqrt() const;
	float Distance(const Math::Vec2& vec) const;
	float DistanceSqrt(const Math::Vec2& vec) const;
	float Cross(const Math::Vec2& vec) const;

	static float Distance(const Math::Vec2& vec1, const Math::Vec2& vec2);
	static float DistanceSqrt(const Math::Vec2& vec1, const Math::Vec2& vec2);

	float x = 0;
	float y = 0;
};
std::ostream& operator<<(std::ostream& os, const Math::Vec2& vec);
//----------------------------------------------

//Math::Vector 3 struct
//----------------------------------------------
struct Vec3
{
	Math::Vec3(float _x = 0, float _y = 0, float _z = 0);
	Math::Vec3(const Math::Vec3& vec);
	Math::Vec3(const Math::Vec3&& vec);
	
	bool operator==(const Math::Vec3& vec) const;
	bool operator!=(const Math::Vec3& vec) const;

	Math::Vec3& operator=(const Math::Vec3& vec);
	Math::Vec3& operator=(const Math::Vec3&& vec);
	Math::Vec3 operator-() const;
	Math::Vec3 operator-(const Math::Vec3& vec) const;
	Math::Vec3 operator-=(const Math::Vec3& vec);
	Math::Vec3 operator+(const Math::Vec3& vec) const;
	Math::Vec3 operator+=(const Math::Vec3& vec);
	Math::Vec3 operator*(const float scalar) const;
	Math::Vec3 operator*(const Matrix<4,4, float>& mat) const;
	Math::Vec3 operator*=(const float scalar);
	Math::Vec3 operator*=(const Matrix<4, 4, float>& mat);
	Math::Vec3 operator/(const float scalar) const;
	Math::Vec3 operator/=(const float scalar);
	Math::Vec3 GetClamped(const float max) const;
	Math::Vec3 Cross(const Math::Vec3& vec) const;
	Math::Vec3 GetNormalized() const;

	void Clamp(const float max);
	void Normalize();

	float Dot(const Math::Vec3& vec) const;
	float Magnitude() const;
	float MagnitudeSqrt() const;
	float Distance(const Math::Vec3& vec) const;
	float DistanceSqrt(const Math::Vec3& vec) const;

	static float Distance(const Math::Vec3& vec1, const Math::Vec3& vec2);
	static float DistanceSqrt(const Math::Vec3& vec1, const Math::Vec3& vec2);

public:
	float x = 0;
	float y = 0;
	float z = 0;

	static const Math::Vec3 Up;
	static const Math::Vec3 Down;
	static const Math::Vec3 Right;
	static const Math::Vec3 Left;
	static const Math::Vec3 Foward;
	static const Math::Vec3 Back;
};
std::ostream& operator<<(std::ostream& os, const Math::Vec3& vec);
//----------------------------------------------

//Math::Vector 4 struct
//----------------------------------------------
struct Vec4
{
	Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 1);
	Vec4(const Math::Vec4& vec);
	Vec4(const Math::Vec4&& vec);

	bool operator==(const Math::Vec4& vec) const;
	bool operator!=(const Math::Vec4& vec) const;


	Vec4& operator=(const Math::Vec4& vec);
	Vec4& operator=(const Math::Vec4&& vec);
	Vec4 operator-() const;
	Vec4 operator-(const Math::Vec4& vec) const;
	Vec4 operator-=(const Math::Vec4& vec);
	Vec4 operator+(const Math::Vec4& vec) const;
	Vec4 operator+=(const Math::Vec4& vec);
	Vec4 operator*(const float scalar) const;
	Vec4 operator*(const Mat44& mat);
	Vec4 operator*=(const float scalar);
	Vec4 operator/(const float scalar) const;
	Vec4 operator/=(const float scalar);


	float Dot(const Math::Vec4& vec) const;

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};

	static const Math::Vec4 Red;
	static const Math::Vec4 Green;
	static const Math::Vec4 Blue;
	static const Math::Vec4 Black;
	static const Math::Vec4 White;
};

typedef Vec4 Color;
std::ostream& operator<<(std::ostream& os, const Math::Vec4& vec);

#define UnitVec2 Math::Vec2(1,1)
#define UnitVec3 Math::Vec3(1,1,1)
#define UnitVec4 Math::Vec4(1,1,1,1)

#define ZeroVec2 Math::Vec2()
#define ZeroVec3 Math::Vec3()
#define ZeroVec4 Math::Vec4()

//----------------------------------------------

}