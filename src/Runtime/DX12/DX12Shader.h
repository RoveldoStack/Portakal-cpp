#pragma once
#include <Runtime/Graphics/Shader.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Shader : public Shader
	{
	public:
		DX12Shader(const ShaderCreateDesc& desc);
		virtual ~DX12Shader() override;

		FORCEINLINE ID3DBlob* GetDXShaderBlob() const noexcept { return mShaderBlob.Get(); }
		FORCEINLINE ID3DBlob* GetDXErrorBlob() const noexcept { return mErrorBlob.Get(); }

	private:
		DXPTR<ID3DBlob> mShaderBlob;
		DXPTR<ID3DBlob> mErrorBlob;

		// Inherited via Shader
		virtual void OnDestroy() override;
	};
}