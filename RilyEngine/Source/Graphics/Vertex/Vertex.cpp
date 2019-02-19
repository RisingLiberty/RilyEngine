#include "stdafx.h"

#include "Vertex.h"

namespace Graphics::Vertex
{


Vertex::Vertex() :
	m_Layout(VertexLayout())
{
}

Vertex::Vertex(const Vertex& vertex):
	m_Layout(vertex.m_Layout),
	m_Data(vertex.m_Data)
{

}


Vertex::Vertex(const Vertex&& vertex):
	m_Layout(vertex.m_Layout),
	m_Data(vertex.m_Data)
{

}

Vertex::~Vertex()
{
	if(m_Data)
		free(m_Data);
}

Vertex& Vertex::operator=(const Vertex& vertex)
{
	m_Layout = vertex.m_Layout;
	m_Data = vertex.m_Data;
	return *this;
}

Vertex& Vertex::operator=(const Vertex&& vertex)
{
	m_Layout = vertex.m_Layout;
	m_Data = vertex.m_Data;
	return *this;
}

void Vertex::Push(const VertexAttribute& attribute)
{
	switch (attribute.DataType)
	{
	case VertexAttributeDataType::UNSIGNED_BYTE:
		this->Push<unsigned char>(attribute.AttributeType, attribute.Count);
		break;
	case VertexAttributeDataType::BYTE:
		this->Push<char>(attribute.AttributeType, attribute.Count);
		break;
	case VertexAttributeDataType::UNSIGNED_INT:
		this->Push<unsigned int>(attribute.AttributeType, attribute.Count);
		break;
	case VertexAttributeDataType::INT:
		this->Push<int>(attribute.AttributeType, attribute.Count);
		break;
	case VertexAttributeDataType::FLOAT:
		this->Push<float>(attribute.AttributeType, attribute.Count);
		break;
	//case VertexAttributeDataType::VEC2:
	//	this->Push<Math::Vec2>(attribute.AttributeType, attribute.Count);
	//	break;
	//case VertexAttributeDataType::VEC3:
	//	this->Push<Math::Vec3>(attribute.AttributeType, attribute.Count);
	//	break;
	//case VertexAttributeDataType::VEC4:
	//	this->Push<Math::Vec4>(attribute.AttributeType, attribute.Count);
	//	break;
	}
}

}