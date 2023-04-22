#include "DX11Swapchain.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Graphics/Framebuffer/FramebufferCreateDesc.h>
#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/DX11/Framebuffer/DX11Framebuffer.h>

namespace Portakal
{
	DX11Swapchain::DX11Swapchain(const SwapchainCreateDesc& desc,DX11Device* pDevice) : Swapchain(desc)
	{
		Win32Window* pWindow = (Win32Window*)pDevice->GetOwnerWindow();
		ASSERT(pWindow != nullptr, "DX11Swapchain", "Target device has no window");
		ID3D11Device* pDX11Device = pDevice->GetDXDevice();
		IDXGIFactory4* pFactory = pDevice->GetDXFactory();

		DXGI_MODE_DESC bufferDesc = {};
		bufferDesc.Width = desc.Width;
		bufferDesc.Height = desc.Height;
		bufferDesc.RefreshRate.Numerator = 0;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGIUtils::GetTextureFormat(desc.ColorFormat);
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.BufferCount = desc.ColorBufferCount;
		swapchainDesc.OutputWindow = pWindow->GetWin32WindowHandle();
		swapchainDesc.Windowed = true;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

		ASSERT(SUCCEEDED(pFactory->CreateSwapChain(pDX11Device, &swapchainDesc, mSwapchain.GetAddressOf())), "DX11Swapchain", "Failed to create swapchain!");
		ASSERT(SUCCEEDED(pFactory->MakeWindowAssociation(pWindow->GetWin32WindowHandle(), DXGI_MWA_NO_ALT_ENTER)), "DX1Swapchain", "Failed to make association with the window");

		/*
		* Create color buffers
		*/
		TextureCreateDesc colorTextureDesc = {};
		colorTextureDesc.Width = desc.Width;
		colorTextureDesc.Height = desc.Height;
		colorTextureDesc.Depth = 1;
		colorTextureDesc.ArrayLevels = 0;
		colorTextureDesc.MipLevels = 1;
		colorTextureDesc.Format = desc.ColorFormat;
		colorTextureDesc.SampleCount = 1;
		colorTextureDesc.Type = TextureType::Texture2D;
		colorTextureDesc.Usage = TextureUsage::RenderTarget;

		Array<Texture*> colorTargets;
		{
			/*
			* Get backbuffer
			*/
			DXPTR<ID3D11Texture2D> pBackBuffer;
			
			mSwapchain->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));
			DXPTR<ID3D11Resource> resource;
			pBackBuffer.As<ID3D11Resource>(&resource);

			colorTargets.Add(pDevice->CreateSwapchainTexture(colorTextureDesc, resource));
		}

		/*
		* Create depth stencil view
		*/
		Texture* pDsv = nullptr;
		if (desc.DepthStencilFormat != TextureFormat::None)
		{
			TextureCreateDesc dsvDesc = {};
			dsvDesc.Width = desc.Width;
			dsvDesc.Height = desc.Height;
			dsvDesc.Depth = 1;
			dsvDesc.ArrayLevels = 1;
			dsvDesc.Format = desc.DepthStencilFormat;
			dsvDesc.MipLevels = 1;
			dsvDesc.SampleCount = 1;
			dsvDesc.Type = TextureType::Texture2D;
			dsvDesc.Usage = TextureUsage::DepthStencil | TextureUsage::Sampled;

			pDsv = pDevice->CreateTexture(dsvDesc);
		}

		/*
		* Set swapchain framebuffer
		*/
		FramebufferCreateDesc framebufferDesc = {};
		framebufferDesc.DepthStencilTarget.ArrayLayer = 0;
		framebufferDesc.DepthStencilTarget.MipLevel = 0;
		framebufferDesc.DepthStencilTarget.pTexture = pDsv;
		FramebufferAttachmentDesc colorAttachment = {};
		colorAttachment.ArrayLayer = 0;
		colorAttachment.MipLevel = 0;
		colorAttachment.pTexture = colorTargets[0];
		framebufferDesc.ColorTargets.Add(colorAttachment);

		Framebuffer* pFramebuffer = pDevice->CreateSwapchainFramebuffer(framebufferDesc);
		SetFramebuffer(pFramebuffer);
	}
	DX11Swapchain::~DX11Swapchain()
	{

	}
	void DX11Swapchain::OnDestroy()
	{

	}
	unsigned int DX11Swapchain::GetCurrentImageIndex() const noexcept
	{
		unsigned int presentCount = 0;
		mSwapchain->GetLastPresentCount(&presentCount);

		return presentCount % GetColorBufferCount();
	}
	void DX11Swapchain::SwapbuffersCore()
	{
		mSwapchain->Present(1u, 0);
	}
	void DX11Swapchain::ResizeCore(const unsigned int width, const unsigned int height)
	{

		DX11Device* pDevice = ((DX11Device*)GetOwnerDevice());
		pDevice->LockImmediateContext();

		/*
		* Delete framebuffer and its textures
		*/
		{
			DX11Framebuffer* pFramebuffer = (DX11Framebuffer*)GetFramebuffer();

			const Array<FramebufferAttachmentDesc> colorAttachments = pFramebuffer->GetColorTargets();
			const FramebufferAttachmentDesc depthStencilAttachment = pFramebuffer->GetDepthStencilTarget();

			pFramebuffer->Destroy();

			for (unsigned int i = 0; i < colorAttachments.GetCursor(); i++)
			{
				colorAttachments[i].pTexture->Destroy();
				colorAttachments[i].pTexture = nullptr;
			}

			if (depthStencilAttachment.pTexture != nullptr)
			{
				depthStencilAttachment.pTexture->Destroy();
			}
		}

		/*
		* Resize swapchain buffers
		*/
		mSwapchain->ResizeBuffers(GetColorBufferCount(), width, height, DXGI_FORMAT_UNKNOWN, 0);

		/*
		* Create color buffers
		*/
		TextureCreateDesc colorTextureDesc = {};
		colorTextureDesc.Width = width;
		colorTextureDesc.Height = height;
		colorTextureDesc.Depth = 1;
		colorTextureDesc.ArrayLevels = 0;
		colorTextureDesc.MipLevels = 1;
		colorTextureDesc.Format = GetColorFormat();
		colorTextureDesc.SampleCount = 1;
		colorTextureDesc.Type = TextureType::Texture2D;
		colorTextureDesc.Usage = TextureUsage::RenderTarget;

		Array<Texture*> colorTargets;
		{
			/*
			* Get backbuffer
			*/
			DXPTR<ID3D11Texture2D> pBackBuffer = nullptr;
			mSwapchain->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));

			DXPTR<ID3D11Resource> resource;
			pBackBuffer.As<ID3D11Resource>(&resource);

			colorTargets.Add(pDevice->CreateSwapchainTexture(colorTextureDesc, resource));
		}

		/*
		* Create depth stencil view
		*/
		Texture* pDsv = nullptr;
		if (GetDepthStencilFormat()!= TextureFormat::None)
		{
			TextureCreateDesc dsvDesc = {};
			dsvDesc.Width = width;
			dsvDesc.Height = height;
			dsvDesc.Depth = 1;
			dsvDesc.ArrayLevels = 1;
			dsvDesc.Format = GetDepthStencilFormat();
			dsvDesc.MipLevels = 1;
			dsvDesc.SampleCount = 1;
			dsvDesc.Type = TextureType::Texture2D;
			dsvDesc.Usage = TextureUsage::DepthStencil | TextureUsage::Sampled;

			pDsv = pDevice->CreateTexture(dsvDesc);
		}

		/*
		* Set swapchain framebuffer
		*/
		FramebufferCreateDesc framebufferDesc = {};
		framebufferDesc.DepthStencilTarget.ArrayLayer = 0;
		framebufferDesc.DepthStencilTarget.MipLevel = 0;
		framebufferDesc.DepthStencilTarget.pTexture = pDsv;
		FramebufferAttachmentDesc colorAttachment = {};
		colorAttachment.ArrayLayer = 0;
		colorAttachment.MipLevel = 0;
		colorAttachment.pTexture = colorTargets[0];
		framebufferDesc.ColorTargets.Add(colorAttachment);

		SetFramebuffer(pDevice->CreateSwapchainFramebuffer(framebufferDesc));

		pDevice->UnlockImmediateContext();
	}
}