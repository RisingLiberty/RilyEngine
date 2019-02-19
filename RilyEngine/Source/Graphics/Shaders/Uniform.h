#pragma once

namespace Graphics::Shader
{


enum class UniformDataType
{
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT33,
	MAT44
};

struct Uniform
{
public:
	Uniform(int Count, UniformDataType type, const std::string& name);
	Uniform(int Count, unsigned int type, const std::string& name);
public:
	unsigned int Size;
	UniformDataType Type;
	std::string Name;
};

}