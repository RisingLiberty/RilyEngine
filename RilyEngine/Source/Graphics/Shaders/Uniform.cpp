#include "stdafx.h"

#include "Uniform.h"

namespace Graphics::Shader
{


Uniform::Uniform(int Count, UniformDataType type, const std::string& name) :
	Size(Count),
	Type(type),
	Name(name)
{
}

Uniform::Uniform(int Count, unsigned int type, const std::string& name) :
	Size(Count),
	Name(name)
{
	switch (type)
	{
	case GL_INT: Type = UniformDataType::INT; break;
	case GL_FLOAT: Type = UniformDataType::FLOAT; break;
	case GL_FLOAT_VEC2: Type = UniformDataType::VEC2; break;
	case GL_FLOAT_VEC3: Type = UniformDataType::VEC3; break;
	case GL_FLOAT_VEC4: Type = UniformDataType::VEC4; break;
	case GL_FLOAT_MAT3: Type = UniformDataType::MAT33; break;
	case GL_FLOAT_MAT4: Type = UniformDataType::MAT44; break;
	}
}

}