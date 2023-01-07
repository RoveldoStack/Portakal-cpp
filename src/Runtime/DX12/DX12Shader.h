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

		FORCEINLINE ID3DBlob* GetDXShaderBlob() const noexcept { return _shaderBlob.Get(); }
		FORCEINLINE ID3DBlob* GetDXErrorBlob() const noexcept { return _errorBlob.Get(); }

	private:
		DXPTR<ID3DBlob> _shaderBlob;
		DXPTR<ID3DBlob> _errorBlob;
	};
}