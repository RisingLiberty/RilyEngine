#pragma once

#include "Renderer.h"

#include "Graphics/Vertex/VertexArray.h"
#include "Graphics/Vertex/VertexLayout.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"

namespace Graphics::Rendering
{
	class RenderObject;

	class BatchRenderer : public Renderer
	{
	public:
		BatchRenderer(Math::Color clearColor);
		~BatchRenderer();

		virtual int Initialize() override;

		void SetLayout(Vertex::VertexLayout* pLayout);

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

		void Submit(const RenderObject* pRenderable) override;
		void Flush();
	
	private:
		Vertex::VertexArray* m_VAO = nullptr;
		Vertex::VertexLayout* m_VertexLayout;
		Buffer::VertexBuffer* m_VertexBuffer = nullptr;
		Buffer::IndexBuffer* m_IndexBuffer = nullptr;
		uint_t m_IndexCount;
	};
}