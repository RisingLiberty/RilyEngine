#include "stdafx.h"

#include "MeshFilter.h"

#include "Content/Mesh.h"

#include "Graphics/Materials/Material.h"

namespace Component
{
	MeshFilter::MeshFilter(Content::Mesh* pMesh, Graphics::Material::Material* pMaterial) :
		m_pMesh(pMesh),
		m_pMaterial(pMaterial)
	{
	}


	MeshFilter::~MeshFilter()
	{
		delete m_pMesh;
		delete m_pMaterial;
	}
}
