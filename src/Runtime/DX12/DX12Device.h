#pragma once
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Core/Core.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_4.h>

namespace Portakal
{
	class PORTAKAL_API DX12Device : public GraphicsDevice
	{
	public:
		DX12Device(const WindowedGraphicsDeviceCreateDesc& desc);
		DX12Device(const StandaloneGraphicsDeviceCreateDesc& desc);
		virtual ~DX12Device() override;


		FORCEINLINE IDXGIFactory4* GetDXFactory() const noexcept { return mFactory.Get(); }
		FORCEINLINE ID3D12Device* GetDXDevice() const noexcept { return mDevice.Get(); }
		FORCEINLINE ID3D12CommandQueue* GetDXGraphicsCmdQueue() const noexcept { return mGraphicsCmdQueue.Get(); }
		FORCEINLINE ID3D12CommandQueue* GetDXComputeCmdQueue() const noexcept { return mComputeCmdQueue.Get(); }
		FORCEINLINE ID3D12CommandAllocator* GetDXGraphicsCmdAllocator() const noexcept { return mGraphicsCmdAllocator.Get(); }
		FORCEINLINE ID3D12CommandAllocator* GetDXComputeCmdAllocator() const noexcept { return mComputeCmdAllocator.Get(); }
		Texture* CreateSwapchainTexture(const DXPTR<ID3D12Resource>& resource, const TextureCreateDesc& desc);
		Framebuffer* CreateSwapchainFramebuffer(const FramebufferCreateDesc& desc, const DXPTR<ID3D12DescriptorHeap> colorHeap, const DXPTR<ID3D12DescriptorHeap> depthStencilHeap);

	protected:
		// Inherited via GraphicsDevice
		virtual GraphicsBackend GetBackend() const noexcept override;
		virtual void SwapbuffersCore() override;
		virtual CommandList* CreateCommandListCore(const CommandListCreateDesc& desc) override;
		virtual GraphicsBuffer* CreateBufferCore(const GraphicsBufferCreateDesc& desc) override;
		virtual Shader* CreateShaderCore(const ShaderCreateDesc& desc) override;
		virtual Texture* CreateTextureCore(const TextureCreateDesc& desc) override;
		virtual Sampler* CreateSamplerCore(const SamplerCreateDesc& desc) override;
		virtual Framebuffer* CreateFramebufferCore(const FramebufferCreateDesc& desc) override;
		virtual Swapchain* CreateSwapchainCore(const SwapchainCreateDesc& desc) override;
		virtual Pipeline* CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc) override;
		virtual Pipeline* CreateComputePipelineCore(const ComputePipelineCreateDesc& desc) override;
		virtual ResourceTable* CreateResourceTableCore(const ResourceTableCreateDesc& desc) override;
		virtual Fence* CreateFenceCore() override;
		virtual void WaitForFinishCore() override;
		virtual void SubmitCommandsCore(const Array<CommandList*>& cmdBuffers) override;
	private:
		void CreateDevice();
	private:
		DXPTR<IDXGIFactory4> mFactory;
		DXPTR<ID3D12Device> mDevice;
		DXPTR<ID3D12CommandQueue> mGraphicsCmdQueue;
		DXPTR<ID3D12CommandQueue> mComputeCmdQueue;
		DXPTR<ID3D12CommandAllocator> mGraphicsCmdAllocator;
		DXPTR<ID3D12CommandAllocator> mComputeCmdAllocator;
		DXPTR<ID3D12Fence> mIdleFence;
		HANDLE mIdleFenceEvent;
		unsigned int mIdleFenceValue;
#ifdef PORTAKAL_DEBUG
		DXPTR<ID3D12Debug> mDebugLayer;
#endif

		
	};
}