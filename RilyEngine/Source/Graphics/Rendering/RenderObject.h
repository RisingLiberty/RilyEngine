#pragma once
namespace Graphics
{
	namespace Buffer
	{
		class VertexBuffer;
		class IndexBuffer;

	}

	namespace Vertex
	{
		class VertexLayout;
	}

	namespace Material
	{
		class Material;
	}
}

namespace Component
{
	class MeshFilter;
}

namespace Graphics::Rendering
{


class RenderObject
{
public:
	RenderObject(Buffer::VertexBuffer* pVertexBuffer, Buffer::IndexBuffer* pIndexBuffer, Vertex::VertexLayout* pVertexLayout, Material::Material* pMaterial, Math::Transform transform, bool shouldRender = true);
	RenderObject(Component::MeshFilter* pMeshFilter, Math::Transform transform, bool shouldRender = true);
	~RenderObject();

	void ShouldRender(bool shouldRender) { m_ShouldRender = shouldRender; }
	bool ShouldRender() const { return m_ShouldRender; }

	Buffer::VertexBuffer* GetVertexBuffer() const { return m_pVertexBuffer; }
	Buffer::IndexBuffer* GetIndexBuffer() const { return m_pIndexBuffer; }

	Vertex::VertexLayout* GetVertexLayout() const { return m_pVertexLayout; }

	Material::Material* GetMaterial() const { return m_pMaterial; }
	Math::Transform GetTransform() const { return m_Transform; }

private:

	Buffer::VertexBuffer* m_pVertexBuffer;
	Buffer::IndexBuffer* m_pIndexBuffer;
	Vertex::VertexLayout* m_pVertexLayout;

	Material::Material* m_pMaterial;
	Math::Transform m_Transform;
	bool m_ShouldRender;
	
};

}