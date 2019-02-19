#include "stdafx.h"

#include "VertexLayout.h"

namespace Graphics::Vertex
{
	void VertexLayout::Clear()
	{
		m_Attributes.Clear();
		m_Size = 0;
	}
}