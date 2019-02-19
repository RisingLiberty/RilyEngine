#include "stdafx.h"

#include "RenderTarget.h"

#if defined WINDOWS_PLATFORM
RenderTarget::RenderTarget(ID3D11Device* pDevice):
	m_pDevice(pDevice)
{
}


RenderTarget::~RenderTarget()
{
	CleanUp();
}

int RenderTarget::Create(RTD desc)
{
	CleanUp();

	if (!desc.IsValid())
		return RENDER_TARGET_INVALID;

	m_Desc = desc;
	m_Math::ColorBufferSupplied = m_Desc.pMath::Color != nullptr;
	m_DepthBufferSupplied = m_Desc.pMath::Color != nullptr;

	uint_t result = CreateMath::Color();
	if (FAILED(result))
	{
		PUSH_ERROR_ID("Failed to create color buffer of render target!", result);
		return result;
	}

	result = CreateDepth();
	if (FAILED(result))
	{
		PUSH_ERROR_ID("Failed to create depth buffer of render target!", result);
		return result;
	}

	return result;
}

ID3D11ShaderResourceView* RenderTarget::GetShaderResourceView() const
{
	if (!m_Desc.EnableMath::ColorSRV)
		PUSH_ERROR("No color SRV created during creation");

	return m_pMath::ColorShaderResourceView;
}

ID3D11ShaderResourceView* RenderTarget::GetDepthShaderResourceView() const
{
	if (!m_Desc.EnableDepthSRV)
		PUSH_ERROR("No depth SRV created during creation");

	return m_pDepthShaderResourceView;
}

int RenderTarget::CreateMath::Color()
{
	uint_t result = OK;

	if (m_Desc.pMath::Color)
	{
		m_pMath::Color = m_Desc.pMath::Color;
		D3D11_TEXTURE2D_DESC texDesc = {};

		m_pMath::Color->GetDesc(&texDesc);
		m_Desc.Width = texDesc.Width;
		m_Desc.Height = texDesc.Height;
		m_Desc.Math::ColorFormat = texDesc.Format;

		m_Desc.EnableMath::ColorSRV = (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE) == D3D11_BIND_SHADER_RESOURCE;
	}

	if (m_Desc.EnableMath::ColorBuffer)
	{
		if (m_Desc.pMath::Color == nullptr)
		{
			D3D11_TEXTURE2D_DESC texDesc = {};
			texDesc.Width = m_Desc.Width;
			texDesc.Height = m_Desc.Height;
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.Format = m_Desc.Math::ColorFormat;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			texDesc.Usage = D3D11_USAGE_DEFAULT;
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | ((m_Desc.EnableMath::ColorSRV) ? D3D11_BIND_SHADER_RESOURCE : 0);
			texDesc.CPUAccessFlags = 0;
			texDesc.MiscFlags = ((m_Desc.GenerateMipMaps_Math::Color) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0);

			result = m_pDevice->CreateTexture2D(&texDesc, nullptr, &m_pMath::Color);
			if (FAILED(result))
			{
				PUSH_ERROR_ID("Failed to create color buffer", result);
				return result;
			}

			m_Desc.pMath::Color = m_pMath::Color;
		}

		result = m_pDevice->CreateRenderTargetView(m_pMath::Color, nullptr, &m_pRenderTargetView);
		if (FAILED(result))
		{
			PUSH_ERROR_ID("Failed to create render target view", result);
			return result;
		}

		if (m_Desc.EnableMath::ColorSRV)
		{
			result = m_pDevice->CreateShaderResourceView(m_pMath::Color, nullptr, &m_pMath::ColorShaderResourceView);
			if (FAILED(result))
			{
				PUSH_ERROR_ID("Failed to create color shader resource view", result);
				return result;
			}
		}
	}
	else
	{
		SafeRelease(m_pMath::Color);
		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pMath::ColorShaderResourceView);
	}

	return result;
}

int RenderTarget::CreateDepth()
{
	uint_t result = OK;

	if (m_Desc.pDepth)
	{
		m_pDepth = m_Desc.pDepth;

		D3D11_TEXTURE2D_DESC texDesc = {};
		m_pDepth->GetDesc(&texDesc);
		m_Desc.Width = texDesc.Width;
		m_Desc.Height = texDesc.Height;
		m_Desc.DepthFormat = texDesc.Format;
	}

	if (m_Desc.EnableDepthBuffer)
	{
		if (m_Desc.pDepth == nullptr)
		{
			D3D11_TEXTURE2D_DESC texDesc = {};
			texDesc.Width = m_Desc.Width;
			texDesc.Height = m_Desc.Height;
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.Format = GetDepthResourceFormat(m_Desc.DepthFormat);
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			texDesc.Usage = D3D11_USAGE_DEFAULT;
			texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | ((m_Desc.EnableDepthSRV) ? D3D11_BIND_SHADER_RESOURCE : 0);
			texDesc.MiscFlags = 0;

			result = m_pDevice->CreateTexture2D(&texDesc, nullptr, &m_pDepth);
			if (FAILED(result))
			{
				PUSH_ERROR_ID("Failed to create depth buffer", result);
				return result;
			}

			m_Desc.pDepth = m_pDepth;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

		dsvDesc.Format = m_Desc.DepthFormat;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		result = m_pDevice->CreateDepthStencilView(m_pDepth, &dsvDesc, &m_pDepthStencilView);
		if (FAILED(result))
		{
			PUSH_ERROR_ID("Failed to create depth stencil view", result);
			return result;
		}

		if (m_Desc.EnableDepthSRV)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = GetDepthSRVFormat(m_Desc.DepthFormat);
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = 1;
			srvDesc.Texture2D.MostDetailedMip = 0;

			result = m_pDevice->CreateShaderResourceView(m_pDepth, &srvDesc, &m_pDepthShaderResourceView);
			if (FAILED(result))
			{
				PUSH_ERROR_ID("Failed to create depth shader resource view", result);
				return result;
			}
		}
	}
	else
	{
		SafeRelease(m_pMath::Color);
		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pMath::ColorShaderResourceView);
	}

	return result;
}

DXGI_FORMAT RenderTarget::GetDepthResourceFormat(DXGI_FORMAT initFormat)
{
	switch (initFormat)
	{
	case DXGI_FORMAT::DXGI_FORMAT_D16_UNORM:
		return DXGI_FORMAT::DXGI_FORMAT_R16_TYPELESS;
	case DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS;
	case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT:
		return DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		return DXGI_FORMAT::DXGI_FORMAT_R32G8X24_TYPELESS;
	default:
		PUSH_ERROR("Depth resource format not supported!");
		return {};
	}
}

DXGI_FORMAT RenderTarget::GetDepthSRVFormat(DXGI_FORMAT initFormat)
{
	switch (initFormat)
	{
	case DXGI_FORMAT::DXGI_FORMAT_D16_UNORM:
		return DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT;
	case DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT:
		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
	case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
	default:
		PUSH_ERROR("depth srv format not supported");
		return {};
	}
}

void RenderTarget::CleanUp()
{
	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pMath::ColorShaderResourceView);
	SafeRelease(m_pDepthShaderResourceView);
	SafeRelease(m_pMath::Color);
	SafeRelease(m_pDepthStencilView);
	SafeRelease(m_pDepth);
}
#endif