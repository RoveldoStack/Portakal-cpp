#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	class PORTAKAL_API DX11Device : public GraphicsDevice
	{
	public:
		DX11Device(const WindowedGraphicsDeviceCreateDesc& desc);
		DX11Device();
		virtual ~DX11Device() override;


		FORCEINLINE IDXGIFactory4* GetDXFactory() const noexcept { return mFactory.Get(); }
		FORCEINLINE IDXGIAdapter1* GetDXAdapter() const noexcept { return mAdapter.Get(); }
		FORCEINLINE ID3D11Device* GetDXDevice() const noexcept { return mDevice.Get(); }
		FORCEINLINE ID3D11DeviceContext* GetDXImmediateContext() const noexcept { return mImmediateContext.Get(); }

		Texture* CreateDXSwapchainTexture(const TextureCreateDesc& desc, const DXPTR<ID3D11Resource>& texture);
		Framebuffer* CreateDXSwapchainFramebuffer(const FramebufferCreateDesc& desc);
		void LockImmediateContext();
		void UnlockImmediateContext();
	private:
		virtual GraphicsBackend GetBackend() const noexcept override { return GraphicsBackend::Directx11; }
		virtual void SwapbuffersCore() override;
		virtual CommandList* CreateGraphicsCommandListCore(const CommandListCreateDesc& desc) override;
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
		virtual void UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc) override;
		virtual void WaitForFinishCore() override;
		virtual void SubmitCommandsCore(const Array<CommandList*>& cmdBuffers) override;
	private:
		PlatformCriticalSection* mContextBarrier;
		ComPtr<IDXGIFactory4> mFactory;
		ComPtr<IDXGIAdapter1> mAdapter;
		ComPtr<ID3D11Device> mDevice;
		ComPtr<ID3D11DeviceContext> mImmediateContext;
	};
}