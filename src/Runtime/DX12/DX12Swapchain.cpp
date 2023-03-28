#include "DX12Swapchain.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/FramebufferAttachmentDesc.h>
#include <Runtime/Graphics/TextureCreateDesc.h>
#include <Runtime/Graphics/FramebufferCreateDesc.h>
#include <Runtime/Graphics/Framebuffer.h>

namespace Portakal
{
    DX12Swapchain::DX12Swapchain(const SwapchainCreateDesc& desc, DX12Device* pDevice) : Swapchain(desc)
    {
		const Win32Window* pWindow = (const Win32Window*)pDevice->GetOwnerWindow();

		/*
		* Create swapchain
		*/
		IDXGIFactory4* pFactory = pDevice->GetDXFactory();
		ID3D12CommandQueue* pCmdQueue = pDevice->GetDXGraphicsCmdQueue();
		ID3D12Device* pDX12Device = pDevice->GetDXDevice();

		DXGI_MODE_DESC modeDesc = {};
		modeDesc.Width = desc.Width;
		modeDesc.Height = desc.Height;
		modeDesc.Format = DXGIUtils::GetTextureFormat(desc.ColorFormat);
		modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		modeDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
		modeDesc.RefreshRate = { 0,0 };

		DXGI_SAMPLE_DESC sampleDesc = { 1,0 };

		DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
		swapchainDesc.BufferCount = desc.ColorBufferCount;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferDesc = modeDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.OutputWindow = pWindow->GetWin32WindowHandle();

		ASSERT(SUCCEEDED(pFactory->CreateSwapChain(pCmdQueue, &swapchainDesc, (IDXGISwapChain**)mSwapchain.GetAddressOf())), "DX12Swapchain", "Failed to create a swapchain");
		ASSERT(SUCCEEDED(pFactory->MakeWindowAssociation(pWindow->GetWin32WindowHandle(), DXGI_MWA_NO_ALT_ENTER)), "DX12Swapchain", "Failed to make association with the window");

		CreateRtvs(pDevice);
    }
	void DX12Swapchain::CreateRtvs(DX12Device* pDevice)
	{
		ID3D12Device* pDXDevice = pDevice->GetDXDevice();

		/*
		* Create color target heap
		*/
		DXPTR<ID3D12DescriptorHeap> colorTargetHeap;

		D3D12_DESCRIPTOR_HEAP_DESC colorTargetHeapDesc = {};
		colorTargetHeapDesc.NumDescriptors = GetColorBufferCount();
		colorTargetHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		colorTargetHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		ASSERT(SUCCEEDED(pDXDevice->CreateDescriptorHeap(&colorTargetHeapDesc, IID_PPV_ARGS(&colorTargetHeap))), "DX12Swapchain", "Failed to create swapchain color heap");

		/*
		* Create color render targets
		*/
		const unsigned int rtvDescriptorSize = pDXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = colorTargetHeap->GetCPUDescriptorHandleForHeapStart();

		Array<FramebufferAttachmentDesc> colorAttachments;
		for (unsigned int i = 0; i < GetColorBufferCount(); i++)
		{
			DXPTR<ID3D12Resource> backBuffer;

			ASSERT(SUCCEEDED(mSwapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffer))), "DX12Swapchain", "Failed to get backbuffer");

			pDXDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, cpuHandle);

			TextureCreateDesc colorTargetDesc = {};
			colorTargetDesc.Width = GetWidth();
			colorTargetDesc.Height = GetHeight();
			colorTargetDesc.Depth = 1;
			colorTargetDesc.Type = TextureType::Texture2D;
			colorTargetDesc.Usage = TextureUsage::ReadOnly | TextureUsage::RenderTarget;
			colorTargetDesc.Format = GetColorFormat();

			Texture* pColorTarget = pDevice->CreateSwapchainTexture(backBuffer, colorTargetDesc);

			FramebufferAttachmentDesc attachment = {};
			attachment.pTexture = pColorTarget;

			colorAttachments.Add(attachment);

			cpuHandle.ptr += rtvDescriptorSize;
		}

		/*
		* Create depth stencil target
		*/
		FramebufferAttachmentDesc depthStencilAttachment = {};

		DXPTR<ID3D12DescriptorHeap> depthStencilHeap;

		if (GetDepthStencilFormat() != TextureFormat::None)
		{
			D3D12_DESCRIPTOR_HEAP_DESC depthStencilHeapDesc = {};
			depthStencilHeapDesc.NumDescriptors = 1;
			depthStencilHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			depthStencilHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			ASSERT(SUCCEEDED(pDXDevice->CreateDescriptorHeap(&depthStencilHeapDesc, IID_PPV_ARGS(&depthStencilHeap))), "DX12Swapchain", "Failed to create swapchain depth stencil heap");
		}

		/*
		* Create framebuffer
		*/
		FramebufferCreateDesc framebufferDesc = {};
		framebufferDesc.ColorTargets = colorAttachments;
		framebufferDesc.DepthStencilTarget = depthStencilAttachment;

		Framebuffer* pFramebuffer = pDevice->CreateSwapchainFramebuffer(framebufferDesc, colorTargetHeap, depthStencilHeap);
		SetFramebuffer(pFramebuffer);
	}
	unsigned int DX12Swapchain::GetCurrentImageIndex() const noexcept
    {
        return mSwapchain->GetCurrentBackBufferIndex();
    }
    void DX12Swapchain::SwapbuffersCore()
    {
		ASSERT(SUCCEEDED(mSwapchain->Present(1, 0)), "DX12Swapchain", "Failed to swap buffers");
    }
    void DX12Swapchain::ResizeCore(const unsigned int width, const unsigned int height)
    {
		LOG("Resized","Reszied");
		/*
		* Delete framebuffer
		*/
		Framebuffer* pFramebuffer = GetFramebuffer();
		if (pFramebuffer != nullptr)
		{
			pFramebuffer->DeleteDeviceObject();
		}

		/*
		* Resize
		*/
		mSwapchain->ResizeBuffers(GetColorBufferCount(),width,height, DXGIUtils::GetTextureFormat(GetColorFormat()), 0);

		/*
		* Create rtvs
		*/
		CreateRtvs((DX12Device*)GetOwnerDevice());

    }
	void DX12Swapchain::OnDestroy()
	{
		mSwapchain.Reset();
	}
}