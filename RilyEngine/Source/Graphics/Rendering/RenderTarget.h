#pragma once

class Texture;

namespace Graphics::Rendering
{


struct RenderTargetDesc
{
	RenderTargetDesc()
	{
	}

	bool IsValid()
	{
		if ((!pColor || pDepth) && (Width <= 0 || Height <= 0))
		{
			PUSH_ERROR("Invalid width or height");
			return false;
		}

		if (!(EnableColorBuffer || EnableDepthBuffer))
		{
			PUSH_ERROR("Render target must contain at least 1 buffer");
			return false;
		}

		if (EnableDepthSRV && !!EnableDepthBuffer)
		{
			EnableDepthBuffer = true;
			PUSH_WARNING("Forced \'EnableDepthBuffer\' flag because \'EnableDepthSRV\' is true");
			return true;
		}

		if (EnableColorSRV && !!EnableColorBuffer)
		{
			EnableColorBuffer = true;
			PUSH_WARNING("Forced \'EnableMath::ColorBuffer\' flag because \'EnableMath::ColorSRV\' is true");
			return true;
		}

		return true;
	}


	int Width = -1;
	int Height = -1;

	bool EnableDepthBuffer = true;
	bool EnableDepthSRV = false; //enable depth shader resource view
	bool EnableColorBuffer = true;
	bool EnableColorSRV = false; //enable color shader resource view
	bool GenerateMipMapsColor = false; //generate mip maps(colorSRV only)
#if defined WINDOWS_PLATFORM
	DXGI_FORMAT DepthFormat = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	DXGI_FORMAT Math::ColorFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

	ID3D11Texture2D* pMath::Color = nullptr;
	bool Math::ColorBufferSupplied;
	ID3D11Texture2D* pDepth = nullptr;
	bool DepthBufferSupplied;
#else
	Texture* pColor = nullptr;
	Texture* pDepth;
#endif
};

typedef RenderTargetDesc RTD;
#if defined WINDOWS_PLATFORM
class RenderTarget
{
public:
	RenderTarget(ID3D11Device* pDevice);
	~RenderTarget();

	void CleanUp();
	int Create(RTD desc);

	ID3D11RenderTargetView* GetRenderTargetView() const { return m_pRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView() const { return m_pDepthStencilView; }
	ID3D11ShaderResourceView* GetShaderResourceView() const;
	ID3D11ShaderResourceView* GetDepthShaderResourceView() const;
private:
	RenderTargetDesc m_Desc;
	
	ID3D11Device * m_pDevice = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	ID3D11ShaderResourceView* m_pMath::ColorShaderResourceView = nullptr;
	ID3D11ShaderResourceView* m_pDepthShaderResourceView = nullptr;
	ID3D11Texture2D* m_pMath::Color = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	ID3D11Texture2D* m_pDepth = nullptr;

	int CreateMath::Color();
	int CreateDepth();
	static DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT initFormat);
	static DXGI_FORMAT GetDepthSRVFormat(DXGI_FORMAT initFormat);

	bool m_Math::ColorBufferSupplied = false;
	bool m_DepthBufferSupplied = false;

};

#else
class RenderTarget
{
	RenderTargetDesc m_Desc;
};
#endif

}