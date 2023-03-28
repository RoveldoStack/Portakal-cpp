#pragma once
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Framebuffer : public Framebuffer
	{
	public:
		DX11Framebuffer(const FramebufferCreateDesc& desc,DX11Device* pDevice);
		DX11Framebuffer(const FramebufferCreateDesc& desc,const Array<ID3D11RenderTargetView*>& rtvs);
		~DX11Framebuffer();

		FORCEINLINE ID3D11RenderTargetView* GetDXSwapchainRTV() const noexcept { return mRtvs[0]; }

		void SetDXRenderTargetViews(const Array<ID3D11RenderTargetView*>& rtvs);
		virtual void OnDestroy() override;
	private:
		Array<ID3D11RenderTargetView*> mRtvs;
	};
}