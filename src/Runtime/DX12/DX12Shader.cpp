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
			&mShaderBlob,
			&mErrorBlob
		);

		ASSERT(mErrorBlob == nullptr, "DX12Shader", "Shader compilation failed with logs: %s", mErrorBlob->GetBufferPointer());
	}
	DX12Shader::~DX12Shader()
	{
		mShaderBlob.Reset();
		mErrorBlob.Reset();
	}
	void DX12Shader::OnDestroy()
	{
		mShaderBlob.Reset();
		mErrorBlob.Reset();
	}
}