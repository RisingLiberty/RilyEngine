#pragma once

#include "../../Settings/DirectXSettings.h"

namespace Component
{
struct Transfrom;
class MeshFilter;
}

namespace Graphics::Rendering
{
class RenderTarget;
class RenderObject;
}

namespace Graphics::Vertex
{
class VertexArray;
}

namespace Graphics::Buffer
{
class IndexBuffer;
}

namespace Graphics::Shader
{
class ShaderProgram;
}

struct ColorBufferDesc
{
	unsigned char RedChannelSize = 8;
	unsigned char GreenChannelSize = 8;
	unsigned char BlueChannelSize = 8;
	unsigned char AlphaChannelSize = 8;
};

struct DepthBufferDesc
{
	unsigned char DepthChannelSize = 16;
	unsigned char StencilChannelSize = 8;
};

class Window;

namespace Graphics::Rendering
{


class Renderer : public Count<Renderer>, public System
{
public:
	Renderer(const Math::Color& clearColor);
	~Renderer();

	virtual int Initialize();
	void ClearScreen() const;

	virtual void PreRender();
	virtual void PostRender();
	virtual void Submit(const RenderObject* pRenderObject);

	virtual void Render();

	ColorBufferDesc GetColorBufferDesc() const { return m_ColorBufferDesc; }
	DepthBufferDesc GetDepthBufferDesc() const { return m_DepthBufferDesc; }

private:

#if defined WINDOWS_PLATFORM
	int InitializeDirectX();
	int CreateAdapter();
	int CreateSwapChain();
	int CreateRenderTarget();

#endif
protected:
	Window* m_pWindow = nullptr;
	Math::Color m_ClearColor = {};

	ColorBufferDesc m_ColorBufferDesc = {};
	DepthBufferDesc m_DepthBufferDesc = {};

	Container::Vector<const RenderObject*> m_ObjectsToRender;

#if defined WINDOW_PLATFORM
	ID3D11Device * m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	IDXGIFactory* m_pDxgiFactory = nullptr;

	D3D11_VIEWPORT m_Viewport;

	DirectXSettings m_DirectXSettings;

#endif
};

}
