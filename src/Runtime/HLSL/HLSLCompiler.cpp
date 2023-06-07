#include "HLSLCompiler.h"
#include <Runtime/D3DCompiler/D3DCompilerUtils.h>
#include <d3dcompiler.h>
#include <Runtime/Memory/Memory.h>
namespace Portakal
{
	void HLSLCompiler::Compile(const String& source, const String& entryPoint, const ShaderStage stage, const unsigned int major, const unsigned int minor, ByteBlock& bytesOut,String& errorOut)
	{
		const String targetString = D3DCompilerUtils::GetCompilerTarget(stage, major, minor);

		ID3DBlob* pShaderBlob;
		ID3DBlob* pErrorBlob;

		D3DCompile(
			source.GetSource(),
			source.GetCursor(),
			nullptr, nullptr, nullptr,
			entryPoint.GetSource(),
			*targetString,
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&pShaderBlob,
			&pErrorBlob
		);

		/*
		* Validate error
		*/
		if (pErrorBlob)
		{
			errorOut = String((char*)pErrorBlob->GetBufferPointer(), pErrorBlob->GetBufferSize());
			pErrorBlob->Release();
			LOG("ShaderHLSL", "Error: %s", *errorOut);
			return;
		}

		/*
		* Copy compiled bytes
		*/
		bytesOut.Copy(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize());
		errorOut = String();

		pShaderBlob->Release();
	}
}