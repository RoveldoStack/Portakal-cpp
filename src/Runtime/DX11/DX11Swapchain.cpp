#include "DX11Swapchain.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Graphics/FramebufferCreateDesc.h>
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
		Array<ID3D11RenderTargetView*> rtvs;
		for (unsigned int i = 0; i < desc.ColorBufferCount; i++)
		{
			/*
			* Get backbuffer
			*/
			ID3D11Texture2D* pBackBuffer = nullptr;
			mSwapchain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));

			/*
			* Create render target view
			*/
			ComPtr<ID3D11RenderTargetView> rtv;
			pDX11Device->CreateRenderTargetView(pBackBuffer, nullptr, rtv.GetAddressOf());
			mRenderTargetViews.Add(rtv);

			/*
			* Release buffer
			*/
			pBackBuffer->Release();
		}

		Framebuffer* pFramebuffer = pDevice->CreateSwapchainFramebuffer({}, rtvs);
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
		ID3D11Device* pDevice = (ID3D11Device*)((DX11Device*)GetOwnerDevice())->GetDXDevice();

		mRenderTargetViews.Clear();

		mSwapchain->ResizeBuffers(0, width, height, DXGIUtils::GetTextureFormat(GetColorFormat()), 0);

		for (unsigned int i = 0; i < GetColorBufferCount(); i++)
		{
			/*
			* Get backbuffer
			*/
			ID3D11Texture2D* pBackBuffer = nullptr;
			mSwapchain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));

			/*
			* Create render target view
			*/
			ComPtr<ID3D11RenderTargetView> rtv;
			pDevice->CreateRenderTargetView(pBackBuffer, nullptr, rtv.GetAddressOf());
			mRenderTargetViews.Add(rtv);

			/*
			* Release buffer
			*/
			pBackBuffer->Release();
		}
	}
}