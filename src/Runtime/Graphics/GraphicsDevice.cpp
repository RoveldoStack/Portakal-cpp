#include "Graphicsdevice.h"
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/GraphicsDeviceObjects.h>
#include <Runtime/Graphics/GraphicsResourceTableCreateDesc.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	GraphicsDevice* GraphicsDevice::CreateStandalone(const StandaloneGraphicsDeviceCreateDesc& desc)
	{
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
				break;
			case Portakal::GraphicsBackend::Directx12:
				break;
			case Portakal::GraphicsBackend::Vulkan:
				break;
			default:
				break;
		}

		/*
		* Validate device
		*/
		ASSERT(pDevice != nullptr, "GraphicsDevice", "Couldnt create the graphics device with the requested backend");

		return pDevice;
	}
	GraphicsDevice::GraphicsDevice(Window* pOwnerWindow)
	{
		_ownerWindow = pOwnerWindow;
		_standalone = false;
		_swapchainFramebuffer = nullptr;
	}
	GraphicsDevice::GraphicsDevice()
	{
		_ownerWindow = nullptr;
		_standalone = true;
		_swapchainFramebuffer = nullptr;
	}
	
	GraphicsDevice::~GraphicsDevice()
	{
		for (unsigned int i = 0; i < _childObjects.GetCursor(); i++)
		{
			GraphicsDeviceObject* pDeviceObject = _childObjects[i];

			delete pDeviceObject;
		}
		_childObjects.Clear();
	}
	void GraphicsDevice::Swapbuffers()
	{
		ASSERT(!_standalone, "GraphicsDevice", "This is a standalone device, you cannot use the swapbuffers on it");

		SwapbuffersCore();
	}
	CommandBuffer* GraphicsDevice::CreateCommandBuffer(const CommandBufferCreateDesc& desc)
	{
		CommandBuffer* pBuffer = CreateCommandBufferCore(desc);

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
	Pipeline* GraphicsDevice::CreatePipeline(const PipelineCreateDesc& desc)
	{
		Pipeline* pPipeline = CreatePipelineCore(desc);

		RegisterChildObject(pPipeline);

		return pPipeline;
	}
	GraphicsResourceTable* GraphicsDevice::CreateResourceTable(const GraphicsResourceTableCreateDesc& desc)
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

		GraphicsResourceTable* pTable = CreateResourceTableCore(desc);

		RegisterChildObject(pTable);

		return pTable;
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
	void GraphicsDevice::SubmitCommands(CommandBuffer* pCmdBuffer)
	{
		SubmitCommandsCore({pCmdBuffer});
	}
	void GraphicsDevice::SubmitCommands(const Array<CommandBuffer*>& cmdBuffers)
	{
		SubmitCommandsCore(cmdBuffers);
	}
	void GraphicsDevice::DeleteChildObject(GraphicsDeviceObject* pObject)
	{
		const int index = _childObjects.FindIndex(pObject);

		if (index == -1)
			return;

		_childObjects.RemoveIndex(index);

		delete pObject;
	}
	void GraphicsDevice::RegisterChildObject(GraphicsDeviceObject* pObject)
	{
		pObject->_SetOwnerDevice(this);

		pObject->Initialize();

		_childObjects.Add(pObject);
	}
	void GraphicsDevice::CreateSwapchainFramebuffer(const SwapchainFramebufferCreateDesc& desc)
	{
		Framebuffer* pFramebuffer = CreateSwapchainFramebufferCore(desc);

		RegisterChildObject(pFramebuffer);

		_swapchainFramebuffer = pFramebuffer;
	}
}