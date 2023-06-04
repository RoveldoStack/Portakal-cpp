#include "HLSLShaderReflectionBlob.h"
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameterUtils.h>
#include <Runtime/Log/Log.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcompiler.inl>
#include <Runtime/Assert/Assert.h>

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
		ASSERT(SUCCEEDED(pConstantBufferReflection->GetDesc(&bufferDesc)), "HLSLShaderReflectionBlob", "Failed to get constant buffer reflection desc: %s", *cBufferName);

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
			ASSERT(SUCCEEDED(pVariableReflection->GetDesc(&variableDesc)), "HLSLShaderReflectionBlob", "Failed to get the variable desc from the constant buffer");

			/*
			* Create new parameter
			*/
			ShaderReflectionBufferParameter bufferParameter = {};
			bufferParameter.Name = variableDesc.Name;
		}

	}
	HLSLShaderReflectionBlob::HLSLShaderReflectionBlob(const ByteBlock& byteBlock)
	{
		/*
		* Get reflection data and validate
		*/
		ID3D11ShaderReflection* pReflectionData = nullptr;
		D3DReflect(byteBlock.GetBlockDataPtr(), byteBlock.GetBlockSizeInBytes(), IID_PPV_ARGS(&pReflectionData));
		ASSERT(pReflectionData != nullptr, "HLSLShaderReflectionBlob", "Failed to get reflection data");

		/*
		* Colllect
		*/
		D3D11_SHADER_DESC shaderDesc = {};
		pReflectionData->GetDesc(&shaderDesc);

		Array<ShaderReflectionResource> entries;
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
			entries.Add(resourceEntry);
		}

		/*
		* Set data
		*/
		SetReflectionData(entries);

		/*
		* Release reflection
		*/
		pReflectionData->Release();
		pReflectionData = nullptr;
	}
}