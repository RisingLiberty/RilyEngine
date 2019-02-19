#include "stdafx.h"

#include "VertexFactory.h"

#include "Vertex.h"

namespace Graphics::Vertex
{

VertexFactory::VertexFactory()
{
}


VertexFactory::~VertexFactory()
{
}

Container::Vector<Vertex*> VertexFactory::BuildVertices(const VertexDesc& desc, uint_t count)
{
	Container::Vector<Vertex*> vertices;

	for (uint_t i = 0; i < count; ++i)
	{
		for (VertexAttribute attrib : desc.Attributes)
		{
			Vertex* vertex = new Vertex();
			vertex->Push(attrib);
			vertices.AddC(vertex);
		}
	}

	return vertices;
}

}