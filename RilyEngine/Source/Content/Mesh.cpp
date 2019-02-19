#include "stdafx.h"

#include "Mesh.h"
#include "Graphics/Vertex/Vertex.h"

namespace Content
{
	Mesh::Mesh(const Container::Vector<Graphics::Vertex::Vertex*>& vertices, const Container::Vector<uint_t>& indices) :
		m_Vertices(std::move(vertices)),
		m_Indices(std::move(indices))
	{
	}


	Mesh::~Mesh()
	{
		m_Vertices.DeleteAllPointers();
	}
}