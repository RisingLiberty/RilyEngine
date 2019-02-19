#pragma once

#include "ComponentBase.h"
#include "../Graphics/Vertex/Vertex.h"

namespace Content
{
	class Mesh;
}

namespace Graphics::Material
{
	class Material;
};

namespace Component
{
	class MeshFilter : public ComponentBase
	{
	public:
		MeshFilter(Content::Mesh* pMesh, Graphics::Material::Material* pMaterial);
		virtual ~MeshFilter();

		Content::Mesh* GetMesh() const { return m_pMesh; }
		Graphics::Material::Material* GetMaterial() const { return m_pMaterial; }

	private:
		Content::Mesh* m_pMesh;
		Graphics::Material::Material* m_pMaterial;
	};
}
