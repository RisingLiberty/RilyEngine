#include "stdafx.h"

#include "Renderer.h"

#include "RenderTarget.h"

#include "Core/Managers/ShaderManager.h"
#include "Core/Managers/SystemManager.h"
#include "Core/System/Window.h"
#include "Core/System/Window.h"

#include "Components/Components.h"

#include "Content/Mesh.h"

#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Context/Context.h"
#include "Graphics/Materials/DefaultMaterial.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Rendering/RenderObject.h"
#include "Graphics/Vertex/Vertex.h"
#include "Graphics/Vertex/VertexArray.h"
#include "Graphics/Vertex/VertexFactory.h"
#include "Graphics/Vertex/VertexLayout.h"
#include "Graphics/Camera.h"


#include "Settings/EngineSettings.h"

namespace Graphics::Rendering
{
	Renderer::Renderer(const Math::Color& clearColor) :
		System(SystemType::RENDERER),
		m_ClearColor(clearColor)
	{
		m_ColorBufferDesc.RedChannelSize = 3;
		m_ColorBufferDesc.GreenChannelSize = 3;
		m_ColorBufferDesc.BlueChannelSize = 2;
		m_ColorBufferDesc.AlphaChannelSize = 0;

		m_DepthBufferDesc.DepthChannelSize = 16;
		m_DepthBufferDesc.StencilChannelSize = 8;
	}


	Renderer::~Renderer()
	{
#if defined WINDOWS_PLATFORM
		SafeRelease(m_pDevice);
		SafeRelease(m_pDeviceContext);
		SafeRelease(m_pSwapChain);
		SafeRelease(m_pDxgiFactory);
#endif
	}

	int Renderer::Initialize()
	{
		System::Initialize();

		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
		glClearDepth(1.0f);


#if defined WINDOWS_PLATFORM
		result = InitializeDirectX();
		if (result != OK) return result;
#endif
		return OK;
	}

	void Renderer::PreRender()
	{
		ClearScreen();
	}

	void Renderer::PostRender()
	{
		Context::Context::GetCurrent()->Show();
	}

	void Renderer::Render()
	{
		for (const RenderObject* pRenderObject : m_ObjectsToRender)
		{
			//Create vertex array
			Vertex::VertexArray va;
			va.BindLayoutToBuffer(pRenderObject->GetVertexBuffer(), pRenderObject->GetVertexLayout());
			
			//bind vertex array
			va.Bind();
			
			//bind index buffer
			pRenderObject->GetIndexBuffer()->Bind();

			//draw
			Context::Context::GetCurrent()->Draw(PrimitiveType::TRIANGLES, pRenderObject->GetIndexBuffer()->GetNrOfIndices());
		}

		m_ObjectsToRender.DeleteAllPointers();
		m_ObjectsToRender.Clear();
	}

	void Renderer::ClearScreen() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		assert(glGetError() == GL_NO_ERROR);
	}

	void Renderer::Submit(const RenderObject* pRenderObject)
	{
		m_ObjectsToRender.AddC(pRenderObject);
	}

}
