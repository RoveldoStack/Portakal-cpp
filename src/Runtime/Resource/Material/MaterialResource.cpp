#include "MaterialResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
namespace Portakal
{
	MaterialResource::MaterialResource()
	{
		mDepthStencilState = {};
		mRasterizerState = {};
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
	}
	MaterialResource::~MaterialResource()
	{
		mOwnerDevice = nullptr;
	}

	void MaterialResource::CreateFromShaders(const Array<ShaderResource*>& shaders)
	{
		/*
		* Free former shaders
		*/
		mShaders.Clear();

		/*
		* Reset former parameter state
		*/
		mStageParameterDescriptors.Clear();
		mResourceState.Slots.Clear();

		/*
		* Validate if given shaders valid
		*/
		Array<PipelineResourceTableDesc> newResourceStateTables;
		unsigned int shaderStageCounts[5] = { 0,0,0,0,0};
		for (unsigned int shaderIndex = 0; shaderIndex < shaders.GetCursor(); shaderIndex++)
		{
			const ShaderResource* pShader = shaders[shaderIndex];
			const ShaderReflectionBlob* pReflectionBlob = pShader->GetReflectionBlob();
			const Shader* pUnderlyingShader = pShader->GetShader();

			if (pShader->IsDestroyed())
			{
				LOG("MaterialResource", "Given shader [%d] was destroyed", shaderIndex);
				return;
			}

			if (pReflectionBlob == nullptr)
			{
				LOG("MaterialResource", "Given shader [%d] was missing reflection blob", shaderIndex);
				return;
			}

			if (!pShader->IsCompiled())
			{
				LOG("MaterialResource", "Given shader [%d] was invalid/failed to compile", shaderIndex);
				return;
			}

			if (pUnderlyingShader->GetStage() == ShaderStage::None)
			{
				LOG("MaterialResource", "Given shader [%d] was marked as ShaderStage::None", shaderIndex);
				return;
			}

			if (shaderStageCounts[(unsigned int)pUnderlyingShader->GetStage()] != 0)
			{
				LOG("MaterialResource", "Duplicate shader found!");
				return;
			}

			/*
			* Collect reflection entries
			*/
			const Array<ShaderReflectionEntry> reflectionEntries = pReflectionBlob->GetEntries();

			/*
			* Create pipeline resource table holders
			*/

			/*
			* Table start locations will be always 0 for now. MaterialResource generilizes the resource access.
			* It gathers all three different resource types into single resource table blocks for (Textures,samplers and buffers).
			* So there will be maximum of three resource table for pipeline resource state at max when using MaterialResource.
			*/
			PipelineResourceTableDesc bufferTableDesc = {};
			bufferTableDesc.Stage = pShader->GetStage();
			bufferTableDesc.StartLocation = 0;

			PipelineResourceTableDesc resourceViewTableDesc = {};
			resourceViewTableDesc.Stage = pShader->GetStage();
			resourceViewTableDesc.StartLocation = 0;

			PipelineResourceTableDesc samplerTableDesc = {};
			samplerTableDesc.Stage = pShader->GetStage();
			samplerTableDesc.StartLocation = 0;

			/*
			* Create stage parameter descriptor
			*/
			MaterialStageParameterDescriptor stageParameterDescriptor = {};

			/*
			* Iterate given reflection blob entries and extract both pipelin resource table descs and material stage&parameter descriptors along the way
			*/
			for (unsigned int entryIndex = 0; entryIndex < reflectionEntries.GetCursor(); entryIndex++)
			{
				const ShaderReflectionEntry& reflectionEntry = reflectionEntries[entryIndex];

				MaterialParameterDescriptor parameterDescriptor = {};
				parameterDescriptor.pData = nullptr;
				parameterDescriptor.SizeInBytes = reflectionEntry.SizeInBytes;
				switch (reflectionEntry.Type)
				{
					case Portakal::ShaderResourceType::Texture:
					{
						resourceViewTableDesc.Entries.Add({ reflectionEntry.Name,PipelineResourceType::ResourceView });
						parameterDescriptor.Type = MaterialParameterType::Texture;

						break;
					}
					case Portakal::ShaderResourceType::Sampler:
					{
						samplerTableDesc.Entries.Add({ reflectionEntry.Name,PipelineResourceType::Sampler });
						parameterDescriptor.Type = MaterialParameterType::Sampler;

						break;
					}
					case Portakal::ShaderResourceType::ConstantBuffer:
					{
						bufferTableDesc.Entries.Add({ reflectionEntry.Name,PipelineResourceType::ConstantBuffer });
						parameterDescriptor.Type = MaterialParameterType::Buffer;

						break;
					}
					default:
						break;
				}

				/*
				* Add another parameter to the stage descriptor
				*/
				stageParameterDescriptor.Parameters.Add(parameterDescriptor);
			}

			/*
			* Validate and register pipeline resource table descs
			*/
			if (bufferTableDesc.Entries.GetCursor() > 0)
			{
				newResourceStateTables.Add(bufferTableDesc);
			}
			if (samplerTableDesc.Entries.GetCursor() > 0)
			{
				newResourceStateTables.Add(samplerTableDesc);
			}
			if (resourceViewTableDesc.Entries.GetCursor() > 0)
			{
				newResourceStateTables.Add(resourceViewTableDesc);
			}

			/*
			* Register paramater stage descriptor
			*/
			mStageParameterDescriptors.Register(pUnderlyingShader->GetStage(), stageParameterDescriptor);

			/*
			* Increment stage count
			*/
			shaderStageCounts[(unsigned int)pUnderlyingShader->GetStage()]++;
		}
		
		/*
		* Get new shaders
		*/
		mShaders = shaders;

		/*
		* Set resource state
		*/
		mResourceState.Slots = newResourceStateTables;
	}

	void MaterialResource::SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture)
	{
		
	}
	void MaterialResource::SetRasterizerState(const RasterizerStateDesc& stateDesc)
	{

	}
	void MaterialResource::SetDepthStencilState(const DepthStencilStateDesc& stateDesc)
	{

	}
	void MaterialResource::SetBlendingState(const BlendingStateDesc& stateDesc)
	{

	}
	void MaterialResource::OnShaderCompiled(ShaderResource* pShader)
	{
		/*
		* Validate shader
		*/
		if (pShader->IsDestroyed())
		{
			LOG("MaterialResource", "OnShaderCompiled event reported an invalid ShaderResource!. Ignoring the event");
			return;
		}

		/*
		* Validate if shader is compiled successfully
		*/
		if (!pShader->IsCompiled())
		{
			LOG("MaterialResource", "OnShaderCompiled event reported a shader with errors. Will ignore the shader in order to prevent crashing in certain graphics APIs such as Vulkan");
			return;
		}

		/*
		* Recreate
		*/
		CreateFromShaders(mShaders);
	}
	TextureResource* MaterialResource::GetTextureParameter(const String& name, const ShaderStage stage) const noexcept
	{
		return nullptr;
	}
	void MaterialResource::DestroyCore()
	{

	}
}