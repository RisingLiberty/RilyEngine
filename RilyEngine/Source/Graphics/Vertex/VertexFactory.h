#pragma once

namespace Graphics::Vertex
{

struct VertexDesc;
class Vertex;

class VertexFactory
{
public:
	VertexFactory();
	~VertexFactory();

	static Container::Vector<Vertex*> BuildVertices(const VertexDesc& desc, uint_t count);
};

}
