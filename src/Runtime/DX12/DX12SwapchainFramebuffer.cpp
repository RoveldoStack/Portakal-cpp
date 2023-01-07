#include "DX12SwapchainFramebuffer.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/TextureCreateDesc.h>
#include <Runtime/Graphics/Texture.h>

namespace Portakal
{
	DX12SwapchainFramebuffer::DX12SwapchainFramebuffer(const SwapchainFramebufferCreateDesc& desc, DX12Device* pDevice) : SwapchainFramebuffer(desc)
	{
		const Win32Window* pWin32Window = (const Win32Window*)pDevice->GetOwnerWindow();

		/*
		* Create swapchain
		*/
		IDXGIFactory4* pFactory = pDevice->GetDXFactory();
		ID3D12CommandQueue* pCmdQueue = pDevice->GetDXCmdQueue();
		ID3D12CommandAllocator* pCmdAllocator = pDevice->GetDXCmdAllocator();
		ID3D12Device* pDX12Device = pDevice->GetDXDevice();

		DXGI_MODE_DESC bufferDesc = {};
		bufferDesc.Width = desc.Width;
		bufferDesc.Height = desc.Height;
		bufferDesc.Format = DXGIUtils::GetTextureFormat(desc.ColorFormat);
		bufferDesc.RefreshRate.Numerator = 0;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;

		DXGI_SAMPLE_DESC sampleDesc = {};
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
		swapchainDesc.BufferCount = desc.BufferCount;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.OutputWindow = pWin32Window->GetWin32WindowHandle();

		ASSERT(SUCCEEDED(pFactory->CreateSwapChain(pCmdQueue, &swapchainDesc, (IDXGISwapChain**)_swapchain.GetAddressOf())), "DX12SwapchainFramebuffer", "Failed to create the swapchain framebuffer");
		ASSERT(SUCCEEDED(pFactory->MakeWindowAssociation(pWin32Window->GetWin32WindowHandle(), DXGI_MWA_NO_ALT_ENTER)), "DX12SwapchainFramebuffer", "Failed to associate with the window");

		/*
		* Create swapchain descriptor heap
		*/
		D3D12_DESCRIPTOR_HEAP_DESC renderTargetHeapDesc = {};
		renderTargetHeapDesc.NumDescriptors = desc.BufferCount;
		renderTargetHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		renderTargetHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		ASSERT(SUCCEEDED(pDX12Device->CreateDescriptorHeap(&renderTargetHeapDesc, IID_PPV_ARGS(&_renderTargetHeap))), "DX12SwapchainFramebuffer", "Failed to create the render target heap descriptor");

		/*
		* Create render targets
		*/
		const unsigned int renderTargetDescriptorSize = pDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_CPU_DESCRIPTOR_HANDLE cpUDescriptorHandle = _renderTargetHeap->GetCPUDescriptorHandleForHeapStart();

		for (unsigned int i = 0; i < desc.BufferCount; i++)
		{
			DXPTR<ID3D12Resource> backBuffer;

			ASSERT(SUCCEEDED(_swapchain->GetBuffer(i, IID_PPV_ARGS(backBuffer.GetAddressOf()))), "DX12SwapchainFramebuffer", "Failed to retrieve swapchain backbuffer");

			pDX12Device->CreateRenderTargetView(backBuffer.Get(), nullptr, cpUDescriptorHandle);

			TextureCreateDesc colorTextureDesc = {};
			colorTextureDesc.Width = desc.Width;
			colorTextureDesc.Height = desc.Height;
			colorTextureDesc.Depth = 1;
			colorTextureDesc.Type = TextureType::Texture2D;
			colorTextureDesc.Usage = TextureUsage::Sampled | TextureUsage::RenderTarget;
			colorTextureDesc.Format = desc.ColorFormat;

			Texture* colorTarget = pDevice->CreateSwapchainTexture(backBuffer, colorTextureDesc);

			colorTarget->SetDeviceObjectName("SwapchainRenderTarget_" + String::GetFromInteger(i));

			_colorTextures.Add(colorTarget);

			cpUDescriptorHandle.ptr += renderTargetDescriptorSize;
		}
	}
	DX12SwapchainFramebuffer::~DX12SwapchainFramebuffer()
	{

	}
	Array<Texture*> DX12SwapchainFramebuffer::GetColorTargets() const noexcept
	{
		Array<Texture*> colorTextures;
		colorTextures.Add(_colorTextures[GetCurrentBackBufferIndex()]);
		return colorTextures;
	}
	D3D12_CPU_DESCRIPTOR_HANDLE DX12SwapchainFramebuffer::GetDXCurrentRenderTargetDescriptor() const noexcept
	{
		ID3D12Device* pDX12Device = ((DX12Device*)GetOwnerDevice())->GetDXDevice();
		const unsigned int rtvDescriptorSize = pDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _renderTargetHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += rtvDescriptorSize * _swapchain->GetCurrentBackBufferIndex();

		return rtvHandle;
	}
	void DX12SwapchainFramebuffer::ResizeCore(const unsigned int width, const unsigned int height)
	{
		DX12Device* pDevice = (DX12Device*)GetOwnerDevice();
		ID3D12Device* pDXDevice = ((const DX12Device*)GetOwnerDevice())->GetDXDevice();

		/*
		* Delete the former render targets
		*/
		for (unsigned int i = 0; i < _colorTextures.GetCursor(); i++)
		{
			GetOwnerDevice()->DeleteChildObject(_colorTextures[i]);
		}
		_colorTextures.Clear();

		/*
		* Resize buffers
		*/
		_swapchain->ResizeBuffers(GetBufferCount(), width, height, DXGIUtils::GetTextureFormat(GetSwapchainColorFormat()), 0);

		/*
		* Create render targets
		*/
		const unsigned int renderTargetDescriptorSize = pDXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_CPU_DESCRIPTOR_HANDLE cpUDescriptorHandle = _renderTargetHeap->GetCPUDescriptorHandleForHeapStart();

		for (unsigned int i = 0; i < GetBufferCount(); i++)
		{
			DXPTR<ID3D12Resource> backBuffer;

			ASSERT(SUCCEEDED(_swapchain->GetBuffer(i, IID_PPV_ARGS(backBuffer.GetAddressOf()))), "DX12SwapchainFramebuffer", "Failed to retrieve swapchain backbuffer");

			pDXDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, cpUDescriptorHandle);
			pDXDevice->SetName(L"Swapchain render target");

			cpUDescriptorHandle.ptr += renderTargetDescriptorSize;

			TextureCreateDesc colorTextureDesc = {};
			colorTextureDesc.Width = width;
			colorTextureDesc.Height = height;
			colorTextureDesc.Depth = 1;
			colorTextureDesc.Type = TextureType::Texture2D;
			colorTextureDesc.Usage = TextureUsage::Sampled | TextureUsage::RenderTarget;
			colorTextureDesc.Format = GetSwapchainColorFormat();

			Texture* colorTarget = pDevice->CreateSwapchainTexture(backBuffer, colorTextureDesc);

			_colorTextures.Add(colorTarget);
		}
	}
	unsigned int DX12SwapchainFramebuffer::GetCurrentBackBufferIndex() const noexcept
	{
		return _swapchain->GetCurrentBackBufferIndex();
	}
}