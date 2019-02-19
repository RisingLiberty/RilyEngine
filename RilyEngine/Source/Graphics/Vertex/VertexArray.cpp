#include "stdafx.h"

#include "VertexArray.h"

#include "VertexLayout.h"

#include "../Buffers/VertexBuffer.h"

#include "Graphics/Context/OpenGLContext.h"

namespace Graphics::Vertex
{


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ID));
}


VertexArray::~VertexArray()
{
}

void VertexArray::BindLayoutToBuffer(const Graphics::Buffer::VertexBuffer* vb, const VertexLayout* pLayout)
{
	this->Bind();
	vb->Bind();

	const Container::Vector<VertexAttribute>& attributes = pLayout->GetAttributes();
	unsigned int offset = 0;

	for (uint_t i = 0; i < attributes.Count(); ++i)
	{
		const VertexAttribute& attribute = attributes[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, attribute.Count, attribute.GetOpenGLDataType(), attribute.IsNormalized, pLayout->GetSize(), (const void*)offset));
		offset += attribute.Count * VertexAttribute::GetSizeOfDataType(attribute.DataType);
	}
}

void VertexArray::Bind() const
{
	Context::Context::GetCurrent()->BindVertexArray(m_ID);
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

}