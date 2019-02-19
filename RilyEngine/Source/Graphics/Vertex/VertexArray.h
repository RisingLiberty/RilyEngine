#pragma once

namespace Graphics::Buffer
{
	class VertexBuffer;
}

namespace Graphics::Vertex
{

class VertexLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void BindLayoutToBuffer(const Buffer::VertexBuffer* vb, const VertexLayout* pLayout);

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_ID;
};

}
