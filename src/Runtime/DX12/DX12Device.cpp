#include "DX12Device.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX12/DX12DeviceObjects.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>

namespace Portakal
{
	DX12Device::DX12Device(const WindowedGraphicsDeviceCreateDesc& desc) : GraphicsDevice(desc.pOwnerWindow)
	{
		CreateDevice();
	}
	DX12Device::DX12Device(const StandaloneGraphicsDeviceCreateDesc& desc)
	{
		CreateDevice();
	}
	DX12Device::~DX12Device()
	{

	}
	Texture* DX12Device::CreateSwapchainTexture(const DXPTR<ID3D12Resource>& resource, const TextureCreateDesc& desc)
	{
		DX12Texture* pTexture = new DX12Texture(resource, desc);

		RegisterChildObject(pTexture);

		return pTexture;
	}
	GraphicsBackend DX12Device::GetBackend() const noexcept
	{
		return GraphicsBackend::Directx12;
	}
	void DX12Device::SwapbuffersCore()
	{
		const DX12SwapchainFramebuffer* pFramebuffer = (const DX12SwapchainFramebuffer*)GetSwapchainFramebuffer();
		ASSERT(SUCCEEDED(pFramebuffer->GetDXSwapchain()->Present(1, 0)), "DX12Device", "Failed to swap the swapchain buffers");
	}
	CommandBuffer* DX12Device::CreateCommandBufferCore(const CommandBufferCreateDesc& desc)
	{
		return new DX12CommandBuffer(desc,this);
	}
	GraphicsBuffer* DX12Device::CreateBufferCore(const GraphicsBufferCreateDesc& desc)
	{
		return new DX12Buffer(desc,this);
	}
	Shader* DX12Device::CreateShaderCore(const ShaderCreateDesc& desc)
	{
		return new DX12Shader(desc);
	}
	Texture* DX12Device::CreateTextureCore(const TextureCreateDesc& desc)
	{
		return new DX12Texture(desc,this);
	}
	Sampler* DX12Device::CreateSamplerCore(const SamplerCreateDesc& desc)
	{
		return new DX12Sampler(desc,this);
	}
	Framebuffer* DX12Device::CreateFramebufferCore(const FramebufferCreateDesc& desc)
	{
		return new DX12Framebuffer(desc,this);
	}
	Framebuffer* DX12Device::CreateSwapchainFramebufferCore(const SwapchainFramebufferCreateDesc& desc)
	{
		return new DX12SwapchainFramebuffer(desc, this);
	}
	Pipeline* DX12Device::CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc)
	{
		return new DX12Pipeline(desc,this);
	}
	Pipeline* DX12Device::CreateComputePipelineCore(const ComputePipelineCreateDesc& desc)
	{
		return nullptr;
	}
	GraphicsResourceTable* DX12Device::CreateResourceTableCore(const GraphicsResourceTableCreateDesc& desc)
	{
		return new DX12ResourceTable(desc,this);
	}
	void DX12Device::UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc)
	{
	}
	void DX12Device::WaitForFinishCore()
	{
		_cmdQueue->Signal(_idleFence.Get(), _idleFenceValue + 1);

		_idleFence->SetEventOnCompletion(_idleFenceValue + 1, _idleFenceEvent);

		WaitForSingleObject(_idleFenceEvent, INFINITE);

		_idleFenceValue++;

		_cmdAllocator->Reset();
	}
	void DX12Device::SubmitCommandsCore(const Array<CommandBuffer*>& cmdBuffers)
	{
		Array<ID3D12CommandList*> cmdLists;
		for (unsigned int i = 0; i < cmdBuffers.GetCursor(); i++)
		{
			const DX12CommandBuffer* pCmdBuffer = (const DX12CommandBuffer*)cmdBuffers[i];

			if (pCmdBuffer == nullptr)
				return;

			cmdLists.Add(pCmdBuffer->GetDXCmdList());
		}

		if (cmdLists.GetCursor() == 0)
			return;

		_cmdQueue->ExecuteCommandLists(cmdLists.GetCursor(), cmdLists.GetData());
	}
	void DX12Device::CreateDevice()
	{
		/*
		* Create debug layer
		*/
		unsigned int factoryFlags = 0;
#ifdef PORTAKAL_DEBUG
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&_debugLayer))))
		{
			_debugLayer->EnableDebugLayer();

			factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif

		ASSERT(SUCCEEDED(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(_factory.GetAddressOf()))), "DX12Device", "Failed to create a dxgi factory");


		/*
		* Select physical gpu
		*/
		IDXGIAdapter1* pAdapter = nullptr;
		unsigned int adapterIndex = 0;
		bool bValidAdapterFound = false;

		while (_factory->EnumAdapters1(adapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 adapterDesc = {};
			pAdapter->GetDesc1(&adapterDesc);

			if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				adapterIndex++;
				continue;
			}

			if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(_device.GetAddressOf()))))
			{
				bValidAdapterFound = true;
				break;
			}

			adapterIndex++;
		}

		/*
		* Validate for proper adapter
		*/
		ASSERT(bValidAdapterFound, "DX12Device", "A valid gpu couldnt be found");

		/*
		* Create command allocator
		*/
		ASSERT(SUCCEEDED(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(_cmdAllocator.GetAddressOf()))), "DX12Device", "Failed to create a command allocator");

		/*
		* Create command queue
		*/
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		cmdQueueDesc.NodeMask = 0;

		ASSERT(SUCCEEDED(_device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(_cmdQueue.GetAddressOf()))), "DX12Device", "Failed to create a command queue");

		/*
		* Create fence
		*/
		ASSERT(SUCCEEDED(_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_idleFence.GetAddressOf()))), "DX12Device", "Failed to create the idle fence!");

		_idleFenceValue = 0;

		_idleFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		ASSERT(_idleFenceEvent != nullptr, "DX12Device", "Failed to create the fence event");
	}
}