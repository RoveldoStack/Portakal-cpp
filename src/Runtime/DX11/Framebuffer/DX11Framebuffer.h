#pragma once
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Framebuffer : public Framebuffer
	{
	public:
		/// <summary>
		/// Used for external framebuffer
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="pDevice"></param>
		DX11Framebuffer(const FramebufferCreateDesc& desc,const bool bSwapchain,DX11Device* pDevice);
		~DX11Framebuffer();

		void DeleteDXResources();
		void ResizeDXSwapchainFramebuffer(const FramebufferCreateDesc& desc);

		FORCEINLINE Array<ID3D11RenderTargetView*> GetDXRtvs() const noexcept;
		FORCEINLINE ID3D11DepthStencilView* GetDXDsv() const noexcept { return mDsv.Get(); }
	private:
		virtual void OnDestroy() override;
		virtual void SetDeviceObjectNameCore(const String& name) override;
	private:
		Array<DXPTR<ID3D11RenderTargetView>> mRtvs;
		DXPTR<ID3D11DepthStencilView> mDsv;
	};
}