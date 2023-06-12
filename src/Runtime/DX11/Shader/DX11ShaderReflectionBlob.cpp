#include "DX11ShaderReflectionBlob.h"
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameterUtils.h>
#include <Runtime/Log/Log.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcompiler.inl>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementSemantic.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementDataFormat.h>
#include <Runtime/Graphics/Shader/ShaderReflectionInputOutputData.h>
#include "DX11ShaderReflectionUtils.h"

namespace Portakal
{
	void CollectConstantBufferData(ID3D11ShaderReflection* pShaderReflection, const String& cBufferName, ShaderReflectionResource& entry)
	{
		/*
		* Get and validate constant buffer reflection
		*/
		ID3D11ShaderReflectionConstantBuffer* pConstantBufferReflection = pShaderReflection->GetConstantBufferByName(*cBufferName);
		if (pConstantBufferReflection == nullptr)
			return;

		/*
		* Get buffer desc
		*/
		D3D11_SHADER_BUFFER_DESC bufferDesc = {};
		ASSERT(SUCCEEDED(pConstantBufferReflection->GetDesc(&bufferDesc)), "DX11ShaderReflectionBlob", "Failed to get constant buffer reflection desc: %s", *cBufferName);

		/*
		* Get buffer size
		*/
		entry.BufferSize = bufferDesc.Size;

		/*
		* Get elements 
		*/
		for (unsigned int i = 0; i < bufferDesc.Variables; i++)
		{
			/*
			* Get variable and type
			*/
			ID3D11ShaderReflectionVariable* pVariableReflection =  pConstantBufferReflection->GetVariableByIndex(i);
			ID3D11ShaderReflectionType* pType = pVariableReflection->GetType();

			/*
			* Get variable desc
			*/
			D3D11_SHADER_VARIABLE_DESC variableDesc = {};
			ASSERT(SUCCEEDED(pVariableReflection->GetDesc(&variableDesc)), "DX11ShaderReflectionBlob", "Failed to get the variable desc from the constant buffer");

			/*
			* Create new parameter
			*/
			ShaderReflectionBufferParameter bufferParameter = {};
			bufferParameter.Name = variableDesc.Name;
		}

	}
	DX11ShaderReflectionBlob::DX11ShaderReflectionBlob(const ByteBlock& byteBlock)
	{
		/*
		* Get reflection data and validate
		*/
		ID3D11ShaderReflection* pReflectionData = nullptr;
		D3DReflect(byteBlock.GetBlockDataPtr(), byteBlock.GetBlockSizeInBytes(), IID_PPV_ARGS(&pReflectionData));
		ASSERT(pReflectionData != nullptr, "DX11ShaderReflectionBlob", "Failed to get reflection data");

		/*
		* Colllect shader desc
		*/
		D3D11_SHADER_DESC shaderDesc = {};
		pReflectionData->GetDesc(&shaderDesc);

		/*
		* Collect reflection resource entries
		*/
		Array<ShaderReflectionResource> resourceEntries;
		for (unsigned int i = 0; i < shaderDesc.BoundResources; i++)
		{
			/*
			* Get resource bind desc
			*/
			D3D11_SHADER_INPUT_BIND_DESC bindDesc = {};
			pReflectionData->GetResourceBindingDesc(i,&bindDesc);

			/*
			* Create reflection entry
			*/
			ShaderReflectionResource resourceEntry = {};
			resourceEntry.Name = bindDesc.Name;
			resourceEntry.BufferSize = 0;

			/*
			* Catch resource type
			*/
			switch (bindDesc.Type)
			{
				case D3D_SIT_CBUFFER:
				{
					resourceEntry.Type = ShaderResourceType::ConstantBuffer;
					CollectConstantBufferData(pReflectionData, resourceEntry.Name, resourceEntry);
					break;
				}
				case D3D_SIT_TEXTURE:
				{
					resourceEntry.Type = ShaderResourceType::Texture;
					break;
				}
				case D3D_SIT_SAMPLER:
				{
					resourceEntry.Type = ShaderResourceType::Sampler;
					break;
				}
				default:
					break;
			}

			/*
			* Add entry
			*/
			resourceEntries.Add(resourceEntry);
		}

		/*
		* Collect input attributes
		*/
		Array<ShaderReflectionInputOutputData> inputs;
		for (unsigned int inputIndex = 0; inputIndex < shaderDesc.InputParameters; inputIndex++)
		{
			/*
			* Get input desc
			*/
			D3D11_SIGNATURE_PARAMETER_DESC inputDesc = {};
			pReflectionData->GetInputParameterDesc(inputIndex,&inputDesc);

			const InputElementSemantic semantic = DX11ShaderReflectionUtils::GetSemantic(inputDesc.SemanticName);
			const unsigned int semanticIndex = inputDesc.SemanticIndex;
			const InputElementDataFormat format = DX11ShaderReflectionUtils::GetFormat(inputDesc.ComponentType,inputDesc.Mask);
			const unsigned char registerIndex = inputDesc.Register;

			ShaderReflectionInputOutputData ioData = {};
			ioData.Format = format;
			ioData.Semantic = semantic;
			ioData.SemanticIndex = semanticIndex;
			ioData.RegisterIndex = registerIndex;

			inputs.Add(ioData);
		}

		/*
		* Collect output attributes
		*/
		Array<ShaderReflectionInputOutputData> outputs;
		for (unsigned int outputIndex = 0; outputIndex < shaderDesc.OutputParameters; outputIndex++)
		{
			/*
			* Get output desc
			*/
			D3D11_SIGNATURE_PARAMETER_DESC outputDesc = {};
			pReflectionData->GetOutputParameterDesc(outputIndex, &outputDesc);

			const InputElementSemantic semantic = DX11ShaderReflectionUtils::GetSemantic(outputDesc.SemanticName);
			const unsigned int semanticIndex = outputDesc.SemanticIndex;
			const InputElementDataFormat format = DX11ShaderReflectionUtils::GetFormat(outputDesc.ComponentType, outputDesc.Mask);
			const unsigned char registerIndex = outputDesc.Register;

			ShaderReflectionInputOutputData ioData = {};
			ioData.Format = format;
			ioData.Semantic = semantic;
			ioData.SemanticIndex = semanticIndex;
			ioData.RegisterIndex = registerIndex;

			outputs.Add(ioData);
		}

		/*
		* Create reflection data
		*/
		ShaderReflectionData reflectionData = {};
		reflectionData.Resources = resourceEntries;
		reflectionData.Inputs = inputs;
		reflectionData.Outputs = outputs;

		/*
		* Set data
		*/
		SetReflectionData(reflectionData);

		/*
		* Release reflection
		*/
		pReflectionData->Release();
		pReflectionData = nullptr;
	}
}