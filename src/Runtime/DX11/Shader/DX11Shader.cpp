#include "DX11Shader.h"
#include <Runtime/D3DCompiler/D3DCompilerUtils.h>
#include <d3dcompiler.h>
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/HLSL/HLSLCompiler.h>

namespace Portakal
{
	DX11Shader::DX11Shader(const ShaderCreateDesc& desc,DX11Device* pDevice) : Shader(desc)
	{
		if (desc.Bytes.GetBlockSizeInBytes() == 0)
			return;

		/*
		* Compile shader
		*/
		const String targetString = D3DCompilerUtils::GetCompilerTarget(desc.Stage, 4, 0);

		/*
		* Create shader
		*/
		switch (desc.Stage)
		{
			case Portakal::ShaderStage::None:
				break;
			case Portakal::ShaderStage::Vertex:
			{
				ASSERT(
					SUCCEEDED(pDevice->GetDXDevice()->CreateVertexShader(desc.Bytes.GetBlockDataPtr(), desc.Bytes.GetBlockSizeInBytes(), 0, mVertexShader.GetAddressOf()))
					, "DX11Shader", "Failed to create vertex shader");
				break;
			}
			case Portakal::ShaderStage::Fragment:
			{
				ASSERT(
					SUCCEEDED(pDevice->GetDXDevice()->CreatePixelShader(desc.Bytes.GetBlockDataPtr(), desc.Bytes.GetBlockSizeInBytes(), 0, mPixelShader.GetAddressOf()))
					, "DX11Shader", "Failed to create pixel shader");
				break;
			}
			case Portakal::ShaderStage::TesellationEval:
			{
				ASSERT(
					SUCCEEDED(pDevice->GetDXDevice()->CreateDomainShader(desc.Bytes.GetBlockDataPtr(), desc.Bytes.GetBlockSizeInBytes(), 0, mDomainShader.GetAddressOf()))
					, "DX11Shader", "Failed to create domain shader");
				break;
			}
			case Portakal::ShaderStage::TesellationControl:
			{
				ASSERT(
					SUCCEEDED(pDevice->GetDXDevice()->CreateHullShader(desc.Bytes.GetBlockDataPtr(), desc.Bytes.GetBlockSizeInBytes(), 0, mHullShader.GetAddressOf()))
					, "DX11Shader", "Failed to create hull shader");
				break;
			}
			case Portakal::ShaderStage::Compute:
			{
				ASSERT(
					SUCCEEDED(pDevice->GetDXDevice()->CreateComputeShader(desc.Bytes.GetBlockDataPtr(), desc.Bytes.GetBlockSizeInBytes(), 0, mComputeShader.GetAddressOf()))
					, "DX11Shader", "Failed to create compute shader");
				break;
			}
			default:
				ASSERT(false, "DX11Shader", "Invalid shader stage!");
				break;
		}

		
	}

	void DX11Shader::OnDestroy()
	{

	}
	void DX11Shader::SetDeviceObjectNameCore(const String& name)
	{
		if (mVertexShader != nullptr)
			mVertexShader->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetCursor(), name.GetSource());
		if (mPixelShader != nullptr)
			mPixelShader->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetCursor(), name.GetSource());
		if (mDomainShader != nullptr)
			mDomainShader->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetCursor(), name.GetSource());
		if (mHullShader != nullptr)
			mHullShader->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetCursor(), name.GetSource());
		if (mComputeShader != nullptr)
			mComputeShader->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetCursor(), name.GetSource());
	}
}