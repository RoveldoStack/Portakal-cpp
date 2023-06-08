#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Shader : public Shader
	{
	public:
		DX11Shader(const ShaderCreateDesc& desc,DX11Device* pDevice);
		~DX11Shader() = default;

		FORCEINLINE DXPTR<ID3D11VertexShader> GetDXVertexShader() const noexcept { return mVertexShader; }
		FORCEINLINE DXPTR<ID3D11PixelShader> GetDXPixelShader() const noexcept { return mPixelShader; }
		FORCEINLINE DXPTR<ID3D11DomainShader> GetDXDomainShader() const noexcept { return mDomainShader; }
		FORCEINLINE DXPTR<ID3D11HullShader> GetDXHullShader() const noexcept { return mHullShader; }
		FORCEINLINE DXPTR<ID3D11ComputeShader> GetDXComputeShader() const noexcept { return mComputeShader; }

	private:
		// Inherited via Shader
		virtual void OnDestroy() override;
		virtual void SetDeviceObjectNameCore(const String& name) override;
	private:
		DXPTR<ID3D11VertexShader> mVertexShader;
		DXPTR<ID3D11PixelShader> mPixelShader;
		DXPTR<ID3D11DomainShader> mDomainShader;
		DXPTR<ID3D11HullShader> mHullShader;
		DXPTR<ID3D11ComputeShader> mComputeShader;

	};
}