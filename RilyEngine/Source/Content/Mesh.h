#pragma once

namespace Graphics::Vertex
{
	class Vertex;
}

namespace Content
{
	class Mesh
	{
	public:
		Mesh(const Container::Vector<Graphics::Vertex::Vertex*>& vertices, const Container::Vector<uint_t>& indices);
		virtual ~Mesh();

		const Container::Vector<Graphics::Vertex::Vertex*>& GetVertices() const { return m_Vertices; }
		uint_t GetNrOfVertices() const { return m_Vertices.Count(); }
		const Container::Vector<uint_t>& GetIndices() const { return m_Indices; }
		uint_t GetNrOfIndices() const { return m_Indices.Count(); }

	private:
		Container::Vector<Graphics::Vertex::Vertex*> m_Vertices = {};
		Container::Vector<uint_t> m_Indices = {};
	};
}