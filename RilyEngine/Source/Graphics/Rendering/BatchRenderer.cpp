#include "stdafx.h"
#include "BatchRenderer.h"

#include "Core/Managers/SystemManager.h"
#include "Core/System/Window.h"

#include "Components/Meshfilter.h"

#include "Content/Mesh.h"

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Context/Context.h"
#include "Graphics/Rendering/RenderObject.h"
#include "Graphics/Materials/Material.h"


namespace Graphics::Rendering
{
	BatchRenderer::BatchRenderer(Math::Color clearColor) :
		Renderer(clearColor)
	{
		
	}

	BatchRenderer::~BatchRenderer()
	{
		SAFE_DELETE(m_VAO);
		SAFE_DELETE(m_VertexBuffer);
		SAFE_DELETE(m_IndexBuffer);
		SAFE_DELETE(m_VertexLayout);
	}

	void BatchRenderer::SetLayout(Vertex::VertexLayout* pLayout)
	{
		m_VertexLayout = pLayout;
	}

	int BatchRenderer::Initialize()
	{
		Renderer::Initialize();

		m_VAO = new Vertex::VertexArray();
		m_VertexBuffer = new Buffer::VertexBuffer();
		m_IndexBuffer = new Buffer::IndexBuffer();
		m_VertexLayout = new Vertex::VertexLayout();

		m_VertexLayout->Push<Math::Vec3>(Vertex::VertexAttributeType::POSITION, 1);
		m_VertexLayout->Push<Math::Vec2>(Vertex::VertexAttributeType::TEXCOORD, 1);
		m_VertexLayout->Push<Math::Vec3>(Vertex::VertexAttributeType::NORMAL, 1);

		return OK;
	}

	void BatchRenderer::Submit(const RenderObject* pRenderObject)
	{
		//Add old vertices with new vertices
		void* newVertices = pRenderObject->GetVertexBuffer()->GetData();
		unsigned int newSize = pRenderObject->GetVertexBuffer()->GetSize();

		void* oldVertices = m_VertexBuffer->GetData();
		unsigned int oldSize = m_VertexBuffer->GetSize();

		byte* combindedVertices = (byte*)malloc(newSize + oldSize);

		memcpy(combindedVertices, oldVertices, oldSize);
		memcpy((void*)&combindedVertices[oldSize], newVertices, newSize);

		unsigned int oldNrOfVertices = oldSize / m_VertexLayout->GetSize();
		unsigned int newNrOfVertices = newSize / m_VertexLayout->GetSize();

		//vertex layout:
		//position: x y z	32bytes | 00 offset
		//uv:		u v		16bytes | 32 offset
		//normal:	x y z	32bytes | 48 offset

		for (unsigned int i = oldNrOfVertices; i < oldNrOfVertices + newNrOfVertices; ++i)
		{
			unsigned int offset = m_VertexLayout->GetSize();

			Math::Vec3 vertexPos;

			//get the first 3 floats
			memcpy(&vertexPos, &combindedVertices[i * offset], sizeof(vertexPos));

			//skip uv
			Math::Vec3 vertexNormal; 

			//get the last 3 floats
			//offset to normal == 5 * sizeof(normal)
			memcpy(&vertexNormal, &combindedVertices[i * offset + 5 * sizeof(float)], sizeof(vertexNormal));

			pRenderObject->GetMaterial()->UpdateVariable("mvp", rlm::CalculateWorldViewProjection(Math::UnitTransform, SystemManager::GetInstance()->GetWindow()->GetCamera()));

			//opengl inverse the multiplcication on shaders 
			//so we need to inverse the matrix here to get the same result.

			Debug::Log(Debug::LogType::FORCE, pRenderObject->GetTransform());

			Debug::Log(Debug::LogType::FORCE, "Before matrix: ", vertexPos);
			
			//Position --> transpose
			auto worldMat = rlm::CalculateWorldMatrix(pRenderObject->GetTransform());

			Debug::Log(Debug::LogType::FORCE, "Matrix:\n", worldMat);

			vertexPos *= worldMat;
			vertexNormal *= worldMat;

			Debug::Log(Debug::LogType::FORCE, "After matrix: ", vertexPos);


			//normalize to negate it's scaling.
			vertexNormal.Normalize();

			memcpy(&combindedVertices[i * offset], &vertexPos.x, sizeof(float) * 3);
			memcpy(&combindedVertices[i * offset + sizeof(float) * 5], &vertexNormal.x, sizeof(float) * 3);
		}

		//Add old indices with new inidices
		const unsigned int* newIndices = pRenderObject->GetIndexBuffer()->GetData();
		unsigned int newCount = pRenderObject->GetIndexBuffer()->GetNrOfIndices();

		const unsigned int* oldIndices = m_IndexBuffer->GetData();
		unsigned int oldCount = m_IndexBuffer->GetNrOfIndices();

		unsigned int* combindedIndices = (unsigned int*)malloc((newCount + oldCount) * sizeof(unsigned int));

		memcpy(combindedIndices, oldIndices, oldCount * sizeof(unsigned int));
		memcpy((void*)&combindedIndices[oldCount], newIndices, newCount * sizeof(unsigned int));


		for (unsigned int i = oldCount; i < oldCount + newCount; ++i)
			combindedIndices[i] += oldNrOfVertices;

		//delete object
		delete pRenderObject;

		//create new vertex buffer and index buffer for new both arrays
		delete m_VertexBuffer;
		delete m_IndexBuffer;

		m_VertexBuffer = new Buffer::VertexBuffer(combindedVertices, newSize + oldSize);
		m_IndexBuffer = new Buffer::IndexBuffer(combindedIndices, newCount + oldCount);	
	}

	void BatchRenderer::PreRender()
	{
		Renderer::PreRender();
	}

	void BatchRenderer::Render()
	{
		//Bind vertex array
		m_VAO->BindLayoutToBuffer(m_VertexBuffer, m_VertexLayout);
		
		//bind index buffer
		m_IndexBuffer->Bind();

		//draw
		Context::Context::GetCurrent()->Draw(PrimitiveType::TRIANGLES, m_IndexBuffer->GetNrOfIndices());
	}

	void BatchRenderer::PostRender()
	{
		Renderer::PostRender();
		Flush();
	}

	void BatchRenderer::Flush()
	{
		m_ObjectsToRender.DeleteAllPointers();
		m_ObjectsToRender.Clear();

		m_VertexBuffer->Clear();
		m_IndexBuffer->Clear();
	}
}