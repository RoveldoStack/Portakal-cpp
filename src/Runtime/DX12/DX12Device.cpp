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
	Framebuffer* DX12Device::CreateSwapchainFramebuffer(const FramebufferCreateDesc& desc, const DXPTR<ID3D12DescriptorHeap> colorHeap, const DXPTR<ID3D12DescriptorHeap> depthStencilHeap)
	{
		DX12Framebuffer* pFramebuffer = new DX12Framebuffer(desc, colorHeap, depthStencilHeap);

		RegisterChildObject(pFramebuffer);

		return pFramebuffer;
	}
	GraphicsBackend DX12Device::GetBackend() const noexcept
	{
		return GraphicsBackend::Directx12;
	}
	void DX12Device::SwapbuffersCore()
	{
		GetSwapchain()->Swapbuffers();
	}
	CommandList* DX12Device::CreateCommandListCore(const CommandListCreateDesc& desc)
	{
		return new DX12GraphicsCommandList(desc,this);
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
	Swapchain* DX12Device::CreateSwapchainCore(const SwapchainCreateDesc& desc)
	{
		return new DX12Swapchain(desc, this);
	}
	Pipeline* DX12Device::CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc)
	{
		return new DX12GraphicsPipeline(desc,this);
	}
	Pipeline* DX12Device::CreateComputePipelineCore(const ComputePipelineCreateDesc& desc)
	{
		return nullptr;
	}
	ResourceTable* DX12Device::CreateResourceTableCore(const ResourceTableCreateDesc& desc)
	{
		return new DX12ResourceTable(desc,this);
	}
	Fence* DX12Device::CreateFenceCore()
	{
		return new DX12Fence(this);
	}
	void DX12Device::WaitForFinishCore()
	{
		/*
		* Wait for compute command queue
		*/
		mComputeCmdQueue->Signal(mIdleFence.Get(), mIdleFenceValue + 1);

		mIdleFence->SetEventOnCompletion(mIdleFenceValue + 1, mIdleFenceEvent);

		WaitForSingleObject(mIdleFenceEvent, INFINITE);

		mIdleFenceValue++;

		/*
		* Wait for graphics command queue
		*/
		mGraphicsCmdQueue->Signal(mIdleFence.Get(), mIdleFenceValue + 1);

		mIdleFence->SetEventOnCompletion(mIdleFenceValue + 1, mIdleFenceEvent);

		WaitForSingleObject(mIdleFenceEvent, INFINITE);

		mIdleFenceValue++;

		/*
		* Reset allocator
		*/
		mGraphicsCmdAllocator->Reset();
		mComputeCmdAllocator->Reset();
	}
	void DX12Device::SubmitCommandsCore(const Array<CommandList*>& cmdBuffers)
	{
		Array<ID3D12CommandList*> graphicsList;
		Array<ID3D12CommandList*> computeList;
		for (unsigned int i = 0; i < cmdBuffers.GetCursor(); i++)
		{
			const CommandList* pCmdList = cmdBuffers[i];
			
			switch (pCmdList->GetCommandQueueType())
			{
				case Portakal::CommandQueueType::Graphics:
					graphicsList.Add(((DX12GraphicsCommandList*)pCmdList)->GetDXCmdList());
					break;
				case Portakal::CommandQueueType::Compute:
					break;
				case Portakal::CommandQueueType::Present:
					break;
				case Portakal::CommandQueueType::Copy:
					break;
				default:
					break;
			}
		}

		if (graphicsList.GetCursor() > 0)
		{
			mGraphicsCmdQueue->ExecuteCommandLists(graphicsList.GetCursor(), graphicsList.GetData());
		}
		if (computeList.GetCursor() > 0)
		{
			mComputeCmdQueue->ExecuteCommandLists(computeList.GetCursor(), computeList.GetData());
		}

	}
	void DX12Device::CreateDevice()
	{
		/*
		* Create debug layer
		*/
		unsigned int factoryFlags = 0;
#ifdef PORTAKAL_DEBUG
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&mDebugLayer))))
		{
			mDebugLayer->EnableDebugLayer();

			factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif

		ASSERT(SUCCEEDED(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(mFactory.GetAddressOf()))), "DX12Device", "Failed to create a dxgi factory");


		/*
		* Select physical gpu
		*/
		IDXGIAdapter1* pAdapter = nullptr;
		unsigned int adapterIndex = 0;
		bool bValidAdapterFound = false;

		while (mFactory->EnumAdapters1(adapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 adapterDesc = {};
			pAdapter->GetDesc1(&adapterDesc);

			if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				adapterIndex++;
				continue;
			}

			if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(mDevice.GetAddressOf()))))
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
		* Create graphics command allocator
		*/
		ASSERT(SUCCEEDED(mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mGraphicsCmdAllocator.GetAddressOf()))), "DX12Device", "Failed to create a graphics command allocator");

		/*
		* Create graphics command queue
		*/
		D3D12_COMMAND_QUEUE_DESC graphicsCmdQueuDesc = {};
		graphicsCmdQueuDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		graphicsCmdQueuDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		graphicsCmdQueuDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		graphicsCmdQueuDesc.NodeMask = 0;

		ASSERT(SUCCEEDED(mDevice->CreateCommandQueue(&graphicsCmdQueuDesc, IID_PPV_ARGS(mGraphicsCmdQueue.GetAddressOf()))), "DX12Device", "Failed to create a graphics command queue");

		/*
		* Create compute command allocator
		*/
		ASSERT(SUCCEEDED(mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(mComputeCmdAllocator.GetAddressOf()))), "DX12Device", "Failed to create a command allocator");

		/*
		* Create compute command queue
		*/
		D3D12_COMMAND_QUEUE_DESC computeCmdQueueDesc = {};
		computeCmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		computeCmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		computeCmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		computeCmdQueueDesc.NodeMask = 0;

		ASSERT(SUCCEEDED(mDevice->CreateCommandQueue(&computeCmdQueueDesc, IID_PPV_ARGS(mComputeCmdQueue.GetAddressOf()))), "DX12Device", "Failed to create a command queue");

		/*
		* Create fence
		*/
		ASSERT(SUCCEEDED(mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(mIdleFence.GetAddressOf()))), "DX12Device", "Failed to create the idle fence!");

		mIdleFenceValue = 0;

		mIdleFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		ASSERT(mIdleFenceEvent != nullptr, "DX12Device", "Failed to create the fence event");
	}
}