#include "stdafx.h"
#include "RenderObject.h"

#include "Components/MeshFilter.h"

#include "Content/Mesh.h"

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"

namespace Graphics::Rendering
{
	RenderObject::RenderObject(Buffer::VertexBuffer* pVertexBuffer, Buffer::IndexBuffer* pIndexBuffer, Vertex::VertexLayout* pVertexLayout, Material::Material* pMaterial, Math::Transform transform, bool shouldRender) :
		m_pVertexBuffer(pVertexBuffer),
		m_pIndexBuffer(pIndexBuffer),
		m_pVertexLayout(pVertexLayout),
		m_pMaterial(pMaterial),
		m_Transform(transform),
		m_ShouldRender(shouldRender)
	{
	}

	RenderObject::RenderObject(Component::MeshFilter* pMeshFilter, Math::Transform transform, bool shouldRender):
		m_pVertexBuffer(new Buffer::VertexBuffer(pMeshFilter->GetMesh()->GetVertices())),
		m_pIndexBuffer(new Buffer::IndexBuffer(pMeshFilter->GetMesh()->GetIndices())),
		m_pMaterial(pMeshFilter->GetMaterial()),
		m_Transform(transform),
		m_ShouldRender(shouldRender)
	{
		m_pVertexLayout = new Vertex::VertexLayout();
		m_pVertexLayout->Push<Math::Vec3>(Vertex::VertexAttributeType::POSITION, 1);
		m_pVertexLayout->Push<Math::Vec2>(Vertex::VertexAttributeType::TEXCOORD, 1);
		m_pVertexLayout->Push<Math::Vec3>(Vertex::VertexAttributeType::NORMAL, 1);
		
	}

	RenderObject::~RenderObject()
	{
		delete m_pVertexBuffer;
		delete m_pIndexBuffer;
		delete m_pVertexLayout;
	}

}