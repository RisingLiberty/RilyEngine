#pragma once

#include "VertexLayout.h"

namespace Graphics::Vertex
{


enum class VertexAttributeType;

struct VertexDesc
{
	Container::Vector<VertexAttribute> Attributes;
};


class Vertex
{
public:
	Vertex();
	Vertex(const Vertex& vertex);
	Vertex(const Vertex&& vertex);
	~Vertex();
	Vertex& operator=(const Vertex& vertex);
	Vertex& operator=(const Vertex&& vertex);

	void Push(const VertexAttribute& attribute);
	void SetData(void* data, unsigned int Count) 
	{ 
		m_Data = (byte*)malloc(Count); 
		memmove(m_Data, data, Count); 
	}

	byte* GetData() const { return m_Data; }

	VertexLayout GetLayout() const { return m_Layout; }

private:
	template <typename T>
	void Push(VertexAttributeType attribType, unsigned int count = 1)
	{
		m_Layout.Push<T>(attribType, count);
	}
private:
	VertexLayout m_Layout;
	byte* m_Data;
};

}