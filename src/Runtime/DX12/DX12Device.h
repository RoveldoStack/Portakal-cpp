#pragma once
#include <Runtime/Graphics/GraphicsDevice.h>
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


		FORCEINLINE IDXGIFactory4* GetDXFactory() const noexcept { return _factory.Get(); }
		FORCEINLINE ID3D12Device* GetDXDevice() const noexcept { return _device.Get(); }
		FORCEINLINE ID3D12CommandQueue* GetDXCmdQueue() const noexcept { return _cmdQueue.Get(); }
		FORCEINLINE ID3D12CommandAllocator* GetDXCmdAllocator() const noexcept { return _cmdAllocator.Get(); }

		Texture* CreateSwapchainTexture(const DXPTR<ID3D12Resource>& resource, const TextureCreateDesc& desc);
	protected:
		// Inherited via GraphicsDevice
		virtual GraphicsBackend GetBackend() const noexcept override;
		virtual void SwapbuffersCore() override;
		virtual CommandBuffer* CreateCommandBufferCore(const CommandBufferCreateDesc& desc) override;
		virtual GraphicsBuffer* CreateBufferCore(const GraphicsBufferCreateDesc& desc) override;
		virtual Shader* CreateShaderCore(const ShaderCreateDesc& desc) override;
		virtual Texture* CreateTextureCore(const TextureCreateDesc& desc) override;
		virtual Sampler* CreateSamplerCore(const SamplerCreateDesc& desc) override;
		virtual Framebuffer* CreateFramebufferCore(const FramebufferCreateDesc& desc) override;
		virtual Framebuffer* CreateSwapchainFramebufferCore(const SwapchainFramebufferCreateDesc& desc) override;
		virtual Pipeline* CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc) override;
		virtual Pipeline* CreateComputePipelineCore(const ComputePipelineCreateDesc& desc) override;
		virtual GraphicsResourceTable* CreateResourceTableCore(const GraphicsResourceTableCreateDesc& desc) override;
		virtual void UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc) override;
		virtual void WaitForFinishCore() override;
		virtual void SubmitCommandsCore(const Array<CommandBuffer*>& cmdBuffers) override;
	private:
		void CreateDevice();
	private:
		DXPTR<IDXGIFactory4> _factory;
		DXPTR<ID3D12Device> _device;
		DXPTR<ID3D12CommandQueue> _cmdQueue;
		DXPTR<ID3D12CommandAllocator> _cmdAllocator;
		DXPTR<ID3D12Fence> _idleFence;
		HANDLE _idleFenceEvent;
		unsigned int _idleFenceValue;
#ifdef PORTAKAL_DEBUG
		DXPTR<ID3D12Debug> _debugLayer;
#endif

		
	};
}