#include "stdafx.h"

#include "Vec.h"

namespace Math
{


//Math::Vector 2 struct
//--------------------------------------------------------------------------------------------
Vec2::Vec2(float _x, float _y):
	x(_x),
	y(_y)
{
}

Vec2::Vec2(const Vec2& vec):
	x(vec.x),
	y(vec.y)
{
}

Vec2::Vec2(const Vec2&& vec):
	x(vec.x),
	y(vec.y)
{
}

bool Vec2::operator==(const Vec2& vec) const
{
	return x == vec.x && y == vec.y;
}

bool Vec2::operator!=(const Vec2& vec) const
{
	return !(*this == vec);
}

Vec2& Vec2::operator=(const Vec2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

Vec2& Vec2::operator=(const Vec2&& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator-(const Vec2 & vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator-=(const Vec2 & vec)
{
	*this = *this - vec;
	return *this;
}

Vec2 Vec2::operator+(const Vec2 & vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator+=(const Vec2 & vec)
{
	*this = *this + vec;
	return *this;
}

Vec2 Vec2::operator*(const float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vec2 Vec2::operator/(const float scalar) const
{
	float revScale = 1 / scalar;
	return *this * revScale;
}

Vec2 Vec2::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

float Vec2::Dot(const Vec2 & vec) const
{
	return x * vec.x + y * vec.y;
}

float Vec2::Magnitude() const
{
	return sqrt(MagnitudeSqrt());
}

float Vec2::MagnitudeSqrt() const
{
	return Dot(*this);
}

float Vec2::Distance(const Vec2& vec) const
{
	return Distance(*this, vec);
}

float Vec2::DistanceSqrt(const Vec2& vec) const
{
	return DistanceSqrt(*this, vec);
}

float Vec2::Cross(const Vec2& vec) const
{
	return x * vec.y / y - y * vec.x;
}

Vec2 Vec2::GetClamped(const float max) const
{
	float scale = max / Magnitude();
	scale = scale < 1.0f ? scale : 1.0f;
	return *this * scale;
}

Vec2 Vec2::GetRightHand() const
{
	return (y, -x);
}

Vec2 Vec2::GetLeftHand() const
{
	return -GetRightHand();
}

Vec2 Vec2::GetNormalized() const
{
	float magnitude = Magnitude();
	if (magnitude == 0)
		return Vec2();

	return *this / magnitude;
}

void Vec2::Clamp(const float max)
{
	*this = this->GetClamped(max);
}

void Vec2::Normalize()
{
	*this = this->GetNormalized();
}

float Vec2::Distance(const Vec2 & vec1, const Vec2 & vec2)
{
	return sqrt(DistanceSqrt(vec1, vec2));
}

float Vec2::DistanceSqrt(const Vec2& vec1, const Vec2& vec2)
{
	return (vec2 - vec1).MagnitudeSqrt();
}
std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
	os << vec.x << ", " << vec.y;
	return os;
}
//--------------------------------------------------------------------------------------------

//Vector 3 struct
//--------------------------------------------------------------------------------------------

const Vec3 Vec3::Up		= Vec3(0, 1, 0);
const Vec3 Vec3::Down	= Vec3(0, -1, 0);
const Vec3 Vec3::Right	= Vec3(1, 0, 0);
const Vec3 Vec3::Left	= Vec3(-1, 0, 0);
const Vec3 Vec3::Foward = Vec3(0, 0, 1);
const Vec3 Vec3::Back	= Vec3(0, 0, -1);

Vec3::Vec3(float _x, float _y, float _z) :
	x(_x),
	y(_y),
	z(_z)
{
}

Vec3::Vec3(const Vec3& vec) :
	x(vec.x),
	y(vec.y),
	z(vec.z)
{
}

Vec3::Vec3(const Vec3&& vec) :
	x(vec.x),
	y(vec.y),
	z(vec.z)
{
}

bool Vec3::operator==(const Vec3& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

bool Vec3::operator!=(const Vec3& vec) const
{
	return !(*this == vec);
}

Vec3& Vec3::operator=(const Vec3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}

Vec3& Vec3::operator=(const Vec3&& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3 & vec) const
{
	return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

Vec3 Vec3::operator-=(const Vec3 & vec)
{
	*this = *this - vec;
	return *this;
}

Vec3 Vec3::operator+(const Vec3 & vec) const
{
	return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

Vec3 Vec3::operator+=(const Vec3 & vec)
{
	*this = *this + vec;
	return *this;
}

Vec3 Vec3::operator*(const float scalar) const
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator*(const Math::Mat44& mat) const
{
	float data[4][1] = { x,y,z,1 };
	Matrix<4, 1, float> vecMat = data;
	vecMat = mat * vecMat;
	return Vec3(vecMat.m[0][0], vecMat.m[1][0], vecMat.m[2][0]);
}

Vec3 Vec3::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vec3 Vec3::operator*=(const Math::Mat44& mat)
{
	*this = *this * mat;
	return *this;
}

Vec3 Vec3::operator/(const float scalar) const
{
	float revScale = 1 / scalar;
	return *this * revScale;
}

Vec3 Vec3::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

Vec3 Vec3::Cross(const Vec3& vec) const
{
	return Vec3(
		y * vec.z - z * vec.y,
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x
	);
}

Vec3 Vec3::GetClamped(const float max) const
{
	float scale = max / Magnitude();
	scale = scale < 1.0f ? scale : 1.0f;
	return *this * scale;
}

Vec3 Vec3::GetNormalized() const
{
	float magnitude = Magnitude();

	if (magnitude == 0)
		return Vec3();

	return *this / magnitude;
}

void Vec3::Clamp(const float max)
{
	*this = this->GetClamped(max);
}

void Vec3::Normalize()
{
	*this = this->GetNormalized();
}

float Vec3::Dot(const Vec3 & vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

float Vec3::Magnitude() const
{
	return sqrt(MagnitudeSqrt());
}

float Vec3::MagnitudeSqrt() const
{
	return Dot(*this);
}

float Vec3::Distance(const Vec3& vec) const
{
	return Distance(*this, vec);
}

float Vec3::DistanceSqrt(const Vec3& vec) const
{
	return DistanceSqrt(*this, vec);
}


float Vec3::Distance(const Vec3 & vec1, const Vec3 & vec2)
{
	return sqrt(DistanceSqrt(vec1, vec2));
}

float Vec3::DistanceSqrt(const Vec3& vec1, const Vec3& vec2)
{
	return (vec2 - vec1).MagnitudeSqrt();
}
std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	os << vec.x << ", " << vec.y << ", " << vec.z;
	return os;
}
//--------------------------------------------------------------------------------------------

//Vector 4 struct
//--------------------------------------------------------------------------------------------
Vec4::Vec4(float _x, float _y, float _z, float _w) :
	x(_x),
	y(_y),
	z(_z),
	w(_w)
{
}

Vec4::Vec4(const Vec4& vec) :
	x(vec.x),
	y(vec.y),
	z(vec.z),
	w(vec.w)
{
}

Vec4::Vec4(const Vec4&& vec) :
	x(vec.x),
	y(vec.y),
	z(vec.z),
	w(vec.w)
{
}

bool Vec4::operator==(const Vec4& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

bool Vec4::operator!=(const Vec4& vec) const
{
	return !(*this == vec);
}

Vec4& Vec4::operator=(const Vec4& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
	return *this;
}

Vec4& Vec4::operator=(const Vec4&& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
	return *this;
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x, -y, -z);
}

Vec4 Vec4::operator-(const Vec4 & vec) const
{
	return Vec4(x - vec.x, y - vec.y, z - vec.z);
}

Vec4 Vec4::operator-=(const Vec4 & vec)
{
	*this = *this - vec;
	return *this;
}

Vec4 Vec4::operator+(const Vec4 & vec) const
{
	return Vec4(x + vec.x, y + vec.y, z + vec.z);
}

Vec4 Vec4::operator+=(const Vec4 & vec)
{
	*this = *this + vec;
	return *this;
}

Vec4 Vec4::operator*(const float scalar) const
{
	return Vec4(x * scalar, y * scalar, z * scalar);
}

Vec4 Vec4::operator*(const Math::Mat44& mat)
{
	float vec[1][4] = { x,y,z,w };
	Matrix<1, 4, float> matVec = vec;
	matVec = matVec * mat;
	return Vec4(matVec.m[0][0], matVec.m[0][1], matVec.m[0][2], matVec.m[0][3]);
}

Vec4 Vec4::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vec4 Vec4::operator/(const float scalar) const
{
	float revScale = 1 / scalar;
	return *this * revScale;
}

Vec4 Vec4::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

float Vec4::Dot(const Vec4& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}
std::ostream& operator<<(std::ostream& os, const Vec4& vec)
{
	os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
	return os;
}

const Math::Color Math::Color::Red = Math::Color(1, 0, 0, 1);
const Math::Color Math::Color::Green = Math::Color(0, 1, 0, 1);
const Math::Color Math::Color::Blue = Math::Color(0, 0, 1, 1);
const Math::Color Math::Color::Black = Math::Color(0, 0, 0, 1);
const Math::Color Math::Color::White = Math::Color(1, 1, 1, 1);

//--------------------------------------------------------------------------------------------
}
