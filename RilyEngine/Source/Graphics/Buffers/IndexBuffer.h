#pragma once

namespace Graphics::Buffer
{


class IndexBuffer
{
public:
	IndexBuffer(const Container::Vector<unsigned int>& indices);
	IndexBuffer(const unsigned int* data = nullptr, unsigned int count = 0);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int GetNrOfIndices() const { return m_Count; }
	const unsigned int* GetData() const { return m_Data; }

	void Clear();

private:
	const unsigned int* m_Data;
	unsigned int m_ID = -1;
	unsigned int m_Count;
};

}
