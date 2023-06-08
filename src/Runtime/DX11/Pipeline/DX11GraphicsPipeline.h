#pragma once
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11GraphicsPipeline : public Pipeline
	{
	public:
		DX11GraphicsPipeline(const GraphicsPipelineCreateDesc& desc, DX11Device* pDevice);
		virtual ~DX11GraphicsPipeline() override;

		FORCEINLINE ID3D11InputLayout* GetDXInputLayout() const noexcept { return mInputLayout.Get(); }
		FORCEINLINE D3D11_PRIMITIVE_TOPOLOGY GetDXTopology() const noexcept { return mTopology; }
		FORCEINLINE ID3D11RasterizerState* GetDXRasterizerState() const noexcept { return mRasterizerState.Get(); }
		FORCEINLINE ID3D11DepthStencilState* GetDXDepthStencilState() const noexcept { return mDepthStencilState.Get(); }
		FORCEINLINE ID3D11BlendState* GetDXBlendState() const noexcept { return mBlendingState.Get(); }
		FORCEINLINE ID3D11VertexShader* GetDXVertexShader() const noexcept { return mVertexShader.Get(); }
		FORCEINLINE ID3D11PixelShader* GetDXPixelShader() const noexcept { return mPixelShader.Get(); }
		FORCEINLINE ID3D11DomainShader* GetDXDomainShader() const noexcept { return mDomainShader.Get(); }
		FORCEINLINE ID3D11HullShader* GetDXHullShader() const noexcept { return mHullShader.Get(); }
		FORCEINLINE ID3D11ComputeShader* GetDXComputeShader() const noexcept { return mComputeShader.Get(); }
	private:
		virtual void OnDestroy() override;
		virtual void SetDeviceObjectNameCore(const String& name) override;
	private:
		DXPTR<ID3D11InputLayout> mInputLayout;
		DXPTR<ID3D11RasterizerState> mRasterizerState;
		DXPTR<ID3D11DepthStencilState> mDepthStencilState;
		DXPTR<ID3D11BlendState> mBlendingState;
		DXPTR<ID3D11VertexShader> mVertexShader;
		DXPTR<ID3D11PixelShader> mPixelShader;
		DXPTR<ID3D11DomainShader> mDomainShader;
		DXPTR<ID3D11HullShader> mHullShader;
		DXPTR<ID3D11ComputeShader> mComputeShader;

		D3D11_PRIMITIVE_TOPOLOGY mTopology;

	};
}