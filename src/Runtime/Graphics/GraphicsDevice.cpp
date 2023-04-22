#include "Graphicsdevice.h"
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/GraphicsDeviceObjects.h>
#include <Runtime/Graphics/Resource/ResourceTableCreateDesc.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Window/WindowChildDeviceAdapter.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Window/Window.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DX11/DX11Device.h>

#include "GraphicsDeviceAPI.h"
namespace Portakal
{
	GraphicsDevice* GraphicsDevice::CreateStandalone(const StandaloneGraphicsDeviceCreateDesc& desc)
	{
		GraphicsDeviceAPI::RegisterStandaloneDevice(nullptr);
		return nullptr;
	}
	GraphicsDevice* GraphicsDevice::CreateWindowed(const WindowedGraphicsDeviceCreateDesc& desc)
	{
		/*
		* Create device
		*/
		GraphicsDevice* pDevice = nullptr;

		switch (desc.Backend)
		{
			case Portakal::GraphicsBackend::Directx11:
			{
				pDevice = new DX11Device(desc);
				break;
			}
			case Portakal::GraphicsBackend::Directx12:
			{
				pDevice = new DX12Device(desc);
				break;
			}
			case Portakal::GraphicsBackend::Vulkan:
				break;
			default:
				break;
		}

		/*
		* Validate device
		*/
		ASSERT(pDevice != nullptr, "GraphicsDevice", "Couldnt create the graphics device with the requested backend");

		/*
		* Bind device
		*/
		WindowChildDeviceAdapter::_BindDeviceAndWindow(desc.pOwnerWindow, pDevice);

		/*
		* Create swapchain
		*/
		SwapchainCreateDesc swapchainDesc = {};
		swapchainDesc.ColorBufferCount = desc.BufferCount;
		swapchainDesc.ColorFormat = desc.ColorFormat;
		swapchainDesc.DepthStencilFormat = desc.DepthStencilFormat;
		swapchainDesc.Width = desc.pOwnerWindow->GetWidth();
		swapchainDesc.Height = desc.pOwnerWindow->GetHeight();

		pDevice->_CreateSwapchain(swapchainDesc);

		GraphicsDeviceAPI::RegisterWindowedDevice(pDevice);

		return pDevice;
	}
	GraphicsDevice::GraphicsDevice(Window* pOwnerWindow)
	{
		mOwnerWindow = pOwnerWindow;
		mStandalone = false;
		mSwapchain = nullptr;
		mMemory = 0;
		mChildObjectBarrier = PlatformCriticalSection::Create();
	}
	GraphicsDevice::GraphicsDevice()
	{
		mOwnerWindow = nullptr;
		mStandalone = true;
		mSwapchain = nullptr;
		mMemory = 0;
		mChildObjectBarrier = PlatformCriticalSection::Create();
	}
	
	GraphicsDevice::~GraphicsDevice()
	{
		mChildObjectBarrier->Lock();

		for (unsigned int i = 0; i < mChildObjects.GetCursor(); i++)
		{
			GraphicsDeviceObject* pDeviceObject = mChildObjects[i];
			pDeviceObject->Destroy();

			delete pDeviceObject;

			i--;
		}

		mChildObjects.Clear();

		mChildObjectBarrier->Release();
	}
	void GraphicsDevice::Swapbuffers()
	{
		ASSERT(!mStandalone, "GraphicsDevice", "This is a standalone device, you cannot use the swapbuffers on it");

		SwapbuffersCore();
	}
	CommandList* GraphicsDevice::CreateGraphicsCommandList(const CommandListCreateDesc& desc)
	{
		CommandList* pBuffer = CreateGraphicsCommandListCore(desc);

		RegisterChildObject(pBuffer);

		return pBuffer;
	}
	GraphicsBuffer* GraphicsDevice::CreateBuffer(const GraphicsBufferCreateDesc& desc)
	{
		GraphicsBuffer* pBuffer = CreateBufferCore(desc);

		RegisterChildObject(pBuffer);

		return pBuffer;
	}
	Shader* GraphicsDevice::CreateShader(const ShaderCreateDesc& desc)
	{
		Shader* pShader = CreateShaderCore(desc);

		RegisterChildObject(pShader);

		return pShader;
	}
	Texture* GraphicsDevice::CreateTexture(const TextureCreateDesc& desc)
	{
		Texture* pTexture = CreateTextureCore(desc);

		RegisterChildObject(pTexture);

		return pTexture;
	}
	Sampler* GraphicsDevice::CreateSampler(const SamplerCreateDesc& desc)
	{
		Sampler* pSampler = CreateSamplerCore(desc);

		RegisterChildObject(pSampler);

		return pSampler;
	}
	Framebuffer* GraphicsDevice::CreateFramebuffer(const FramebufferCreateDesc& desc)
	{
		Framebuffer* pFramebuffer = CreateFramebufferCore(desc);

		RegisterChildObject(pFramebuffer);

		return pFramebuffer;
	}
	Pipeline* GraphicsDevice::CreateGraphicsPipeline(const GraphicsPipelineCreateDesc& desc)
	{
		Pipeline* pPipeline = CreateGraphicsPipelineCore(desc);

		RegisterChildObject(pPipeline);

		return pPipeline;
	}
	Pipeline* GraphicsDevice::CreateComputePipeline(const ComputePipelineCreateDesc& desc)
	{
		Pipeline* pPipeline = CreateComputePipelineCore(desc);

		RegisterChildObject(pPipeline);

		return pPipeline;
	}
	ResourceTable* GraphicsDevice::CreateResourceTable(const ResourceTableCreateDesc& desc)
	{
		/*
		* Validate resources
		*/
		for (unsigned int i = 0; i < desc.Resources.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pDeviceObject = desc.Resources[i];
			const GraphicsDeviceObjectType type = pDeviceObject->GetDeviceObjectType();

			ASSERT(type == GraphicsDeviceObjectType::Buffer || type == GraphicsDeviceObjectType::Texture || type == GraphicsDeviceObjectType::Sampler, "GraphicsDevice", "Invalid graphics device object as resource!");
		}

		ResourceTable* pTable = CreateResourceTableCore(desc);

		RegisterChildObject(pTable);

		return pTable;
	}
	Fence* GraphicsDevice::CreateFence()
	{
		Fence* pFence = CreateFenceCore();

		RegisterChildObject(pFence);

		return pFence;
	}
	void GraphicsDevice::UpdateBuffer(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc)
	{
		ASSERT(pBuffer != nullptr, "GraphicsDevice", "You cannot update a null GraphicsBuffer");

		UpdateBufferCore(pBuffer, desc);
	}
	void GraphicsDevice::WaitForFinish()
	{
		WaitForFinishCore();
	}
	void GraphicsDevice::SubmitCommands(CommandList* pCmdBuffer)
	{
		if (pCmdBuffer == nullptr)
			return;

		SubmitCommandsCore({pCmdBuffer});
	}
	void GraphicsDevice::SubmitCommands(const Array<CommandList*>& cmdBuffers)
	{
		SubmitCommandsCore(cmdBuffers);
	}
	void GraphicsDevice::RegisterChildObject(GraphicsDeviceObject* pObject)
	{
		mChildObjectBarrier->Lock();

		pObject->_SetOwnerDevice(this);

		mChildObjects.Add(pObject);

		mChildObjectBarrier->Release();
	}
	void GraphicsDevice::_CreateSwapchain(const SwapchainCreateDesc& desc)
	{
		Swapchain* pSwapchain = CreateSwapchainCore(desc);

		RegisterChildObject(pSwapchain);

		mChildObjectBarrier->Lock();
		mSwapchain = pSwapchain;
		mChildObjectBarrier->Release();
	}
	void GraphicsDevice::_NotifyChildObjectDestroyed(GraphicsDeviceObject* pObject)
	{
		mChildObjectBarrier->Lock();
		const int index = mChildObjects.FindIndex(pObject);

		if (index == -1)
		{
			mChildObjectBarrier->Release();
			return;
		}

		mChildObjects.RemoveIndex(index);

		mChildObjectBarrier->Release();
	}
}