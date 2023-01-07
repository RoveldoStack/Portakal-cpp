#include "DX12Shader.h"
#include <Runtime/D3DCompiler/D3DCompilerUtils.h>
#include <d3dcompiler.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	DX12Shader::DX12Shader(const ShaderCreateDesc& desc) : Shader(desc)
	{
		/*
		* Compile shader
		*/
		const String targetString = D3DCompilerUtils::GetCompilerTarget(desc.Stage, 4, 0);
		D3DCompile(
			desc.Source.GetSource(),
			desc.Source.GetCursor(),
			nullptr,nullptr,nullptr,
			desc.EntryPoint.GetSource(),
			*targetString,
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&_shaderBlob,
			&_errorBlob
		);

		ASSERT(_errorBlob == nullptr, "DX12Shader", "Shader compilation failed with logs: %s", _errorBlob->GetBufferPointer());
	}
	DX12Shader::~DX12Shader()
	{
		_shaderBlob.Reset();
		_errorBlob.Reset();
	}
}