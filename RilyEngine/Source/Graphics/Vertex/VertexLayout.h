#pragma once

#include "VertexAttribute.h"

namespace Graphics::Vertex
{


class VertexLayout
{
public:
	VertexLayout() :
		m_Size(0)
	{
	}

	template <typename T>
	void Push(VertexAttributeType type, unsigned int count = 1)
	{
		ASSERT(false, "vertex attribute not recognised");
	}

	template <>
	void Push<float>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::FLOAT, false, count));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::FLOAT);
	}

	template <>
	void Push<unsigned int>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::UNSIGNED_INT, false, count));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::UNSIGNED_INT);
	}

	template <>
	void Push<int>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::INT, false, count));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::INT);
	}

	template <>
	void Push<unsigned char>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::UNSIGNED_BYTE, true, count));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::UNSIGNED_BYTE);
	}

	template <>
	void Push<char>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::BYTE, false, count));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::BYTE);
	}

	template <>
	void Push<Math::Vec2>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::FLOAT, false, count * 2));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::FLOAT) * 2;
	}

	template <>
	void Push<Math::Vec3>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::FLOAT, false, count * 3));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::FLOAT) * 3;
	}

	template <>
	void Push<Math::Vec4>(VertexAttributeType type, unsigned int count)
	{
		m_Attributes.AddM(VertexAttribute(type, VertexAttributeDataType::FLOAT, false, count * 4));
		m_Size += count * VertexAttribute::GetSizeOfDataType(VertexAttributeDataType::FLOAT) * 4;
	}

	const Container::Vector<VertexAttribute>& GetAttributes() const { return m_Attributes; }
	unsigned int GetSize() const { return m_Size; }

	void Clear();

private:
	Container::Vector<VertexAttribute> m_Attributes;
	unsigned int m_Size;
};

}