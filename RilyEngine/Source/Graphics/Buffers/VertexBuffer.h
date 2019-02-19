#pragma once

#include "../Vertex/Vertex.h"

namespace Graphics::Buffer
{


class VertexBuffer
{
public:
	VertexBuffer(const Container::Vector<Graphics::Vertex::Vertex*>& vertices = {});
	VertexBuffer(byte* data, unsigned int Count);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	byte* GetData() const { return m_Data; }
	unsigned int GetSize() { return m_Size; }
	unsigned int GetID() { return m_ID; }

	void Clear();

private:
	byte* m_Data = nullptr;
	unsigned int m_Size = 0;
	unsigned int m_ID;
};

}
