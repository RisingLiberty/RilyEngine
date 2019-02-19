#include "stdafx.h"

#include "VertexBuffer.h"

#include "Graphics/Context/OpenGLContext.h"

namespace Graphics::Buffer
{


VertexBuffer::VertexBuffer(const Container::Vector<Graphics::Vertex::Vertex*>& vertices)
{
	GLCall(glGenBuffers(1, &m_ID));
	
	if (!vertices.IsEmpty())
	{
		unsigned int vertexSize = vertices.First()->GetLayout().GetSize();
		m_Size = vertexSize * vertices.Count(); //sizeof 1 vertex * nr of vertices
		m_Data = (byte*)malloc(m_Size);

		unsigned int offset = 0;
		for (const Graphics::Vertex::Vertex* vertex : vertices)
		{
			memcpy((void*)&m_Data[offset], vertex->GetData(), vertexSize);
			offset += vertexSize;
		}

		this->Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW));
	}
}

VertexBuffer::VertexBuffer(byte* data, unsigned int Count):
	m_Data(data),
	m_Size(Count)
{
	GLCall(glGenBuffers(1, &m_ID));

	this->Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_ID));
	free(m_Data);
}

void VertexBuffer::Bind() const
{
	Context::Context::GetCurrent()->BindVertexBuffer(m_ID);
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Clear()
{
	free(m_Data);
	m_Data = nullptr;
	m_Size = 0;
}

}
