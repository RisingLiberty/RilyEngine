#include "stdafx.h"

#include "IndexBuffer.h"

#include "Graphics/Context/OpenGLContext.h"

namespace Graphics::Buffer
{


	IndexBuffer::IndexBuffer(const Container::Vector<unsigned int>& indices)
	{
		GLCall(glGenBuffers(1, &m_ID));

		if (!indices.IsEmpty())
		{
			m_Count = indices.Count();
			m_Data = (unsigned int*)malloc(sizeof(unsigned int) * m_Count);
			memcpy((void*)m_Data, indices.RawData(), sizeof(unsigned int) * indices.Count());
		}

		this->Bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, GL_STATIC_DRAW));
	}

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
		m_Data(data),
		m_Count(count)
	{
		GLCall(glGenBuffers(1, &m_ID));

		//needs to be bound in order to fill it's data
		this->Bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		Clear();
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::Bind() const
	{
		Context::Context::GetCurrent()->BindIndexBuffer(m_ID);
	}

	void IndexBuffer::UnBind() const
	{
		Context::Context::GetCurrent()->BindIndexBuffer(0);
	}

	void IndexBuffer::Clear()
	{
		if (m_Count > 0)
			free((void*)m_Data);

		m_Data = nullptr;
		m_Count = 0;
	}

}
