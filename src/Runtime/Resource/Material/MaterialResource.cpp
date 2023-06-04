#include "MaterialResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/Sampler/SamplerResource.h>
#include <Runtime/Graphics/Command/CommandList.h>


namespace Portakal
{
	MaterialResource::MaterialResource()
	{
		mDepthStencilState = {};
		mRasterizerState = {};
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();

		/*
		* Create command list
		*/
		mCmdList = mOwnerDevice->CreateCommandList({});
	}
	MaterialResource::~MaterialResource()
	{
		mOwnerDevice = nullptr;
	}

	TextureResource* MaterialResource::GetTextureParameter(const String& name, const ShaderStage stage) const noexcept
	{
		return nullptr;
	}
	void MaterialResource::Create(const Array<ShaderResource*>& shaders)
	{
		/*
		* Remove former signals
		*/
		RemoveFormerShaderSignalEventDelegates();

		/*
		* Free former shaders
		*/
		mShaders.Clear();

		/*
		* Set new shaders
		*/
		mShaders = shaders;

		/*
		* Invalidate
		*/
		Invalidate();
	}

	void MaterialResource::Create(const Array<ShaderResource*>& shaders, const RasterizerStateDesc& rasterizerDesc, const DepthStencilStateDesc& depthStencilDesc, const BlendingStateDesc& blendingDesc)
	{
		/*
		* Set material states upfront
		*/
		mRasterizerState = rasterizerDesc;
		mDepthStencilState = depthStencilDesc;
		mBlendingState = blendingDesc;

		/*
		* Create via shaders
		*/
		Create(shaders);
	}

	void MaterialResource::SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture)
	{
		/*
		* Try find shader stage
		*/
		MaterialStageParameterDescriptor* pStageDescriptor = mStageParameterDescriptors.GetEntryValue(stage);
		if (pStageDescriptor == nullptr)
			return;

		/*
		* Try find parameter with name
		*/
		MaterialParameterDescriptor* pParameterDescriptor = pStageDescriptor->Parameters.GetEntryValue(name);
		if (pParameterDescriptor == nullptr)
			return;

		/*
		* Validate if values are equal
		*/
		if (pTexture == pParameterDescriptor->pData)
			return;

		/*
		* Set value
		*/
		if (pTexture == nullptr) // assing default
		{

		}
		else
		{
			pParameterDescriptor->pData = pTexture;
		}

		/*
		* Invalidate resource state
		*/
		InvalidateResourceTables();

		/*
		* Signal material resource changed
		*/
		SignalMaterialStateChanged();
	}
	void MaterialResource::SetSamplerParameter(const String& name, const ShaderStage stage, SamplerResource* pSampler)
	{
		/*
		* Try find shader stage
		*/
		MaterialStageParameterDescriptor* pStageDescriptor = mStageParameterDescriptors.GetEntryValue(stage);
		if (pStageDescriptor == nullptr)
			return;

		/*
		* Try find parameter with name
		*/
		MaterialParameterDescriptor* pParameterDescriptor = pStageDescriptor->Parameters.GetEntryValue(name);
		if (pParameterDescriptor == nullptr)
			return;

		/*
		* Validate if values are equal
		*/
		if (pSampler == pParameterDescriptor->pData)
			return;

		/*
		* Set value
		*/
		if (pSampler == nullptr) // assing default
		{

		}
		else
		{
			pParameterDescriptor->pData = pSampler;
		}

		/*
		* Invalidate resource state
		*/
		InvalidateResourceTables();

		/*
		* Signal material resource changed
		*/
		SignalMaterialStateChanged();
	}
	void MaterialResource::SetBufferParameter(const String& name, const ShaderStage& stage, GraphicsBuffer* pBuffer)
	{
		/*
		* Try find shader stage
		*/
		MaterialStageParameterDescriptor* pStageDescriptor = mStageParameterDescriptors.GetEntryValue(stage);
		if (pStageDescriptor == nullptr)
			return;

		/*
		* Try find parameter with name
		*/
		MaterialParameterDescriptor* pParameterDescriptor = pStageDescriptor->Parameters.GetEntryValue(name);
		if (pParameterDescriptor == nullptr)
			return;

		/*
		* Validate if values are equal
		*/
		if (pBuffer == pParameterDescriptor->pData)
			return;

		/*
		* Set vlaue
		*/
		if (pBuffer == nullptr) // assing default
		{

		}
		else
		{
			pParameterDescriptor->pData = pBuffer;
		}

		/*
		* Invalidate resource state
		*/
		InvalidateResourceTables();

		/*
		* Signal material resource changed
		*/
		SignalMaterialStateChanged();
	}
	void MaterialResource::SetRasterizerState(const RasterizerStateDesc& stateDesc)
	{
		mRasterizerState = stateDesc;
		SignalMaterialStateChanged();
	}
	void MaterialResource::SetDepthStencilState(const DepthStencilStateDesc& stateDesc)
	{
		mDepthStencilState = stateDesc;
		SignalMaterialStateChanged();
	}
	void MaterialResource::SetBlendingState(const BlendingStateDesc& stateDesc)
	{
		mBlendingState = stateDesc;
		SignalMaterialStateChanged();
	}
	void MaterialResource::RegisterStateChangedDelegate(const Delegate<void, MaterialResource*>& del)
	{
		mStateChangedEvent += del;
	}
	void MaterialResource::RemoveStateChangedDelegate(const Delegate<void, MaterialResource*>& del)
	{
		mStateChangedEvent -= del;
	}
	void MaterialResource::Invalidate()
	{
		InvalidateMaterialState();
		InvalidateResourceTables();
	}
	
	void MaterialResource::InvalidateMaterialState()
	{
		/*
		* Cache the resource registry
		*/
		Registry<ShaderStage, MaterialStageParameterDescriptor> cachedStageParameters = mStageParameterDescriptors;

		/*
		* Clear the current stage parameter descriptors
		*/
		mStageParameterDescriptors.Clear();

		/*
		* Validate if all shaders are valid
		* If only all shaders then new material state can be created
		*/
		unsigned int shaderStageCounts[5] = { 0,0,0,0,0 };
		for (unsigned int i = 0; i < mShaders.GetCursor(); i++)
		{
			const ShaderResource* pShader = mShaders[i];
			const ShaderReflectionBlob* pReflectionBlob = pShader->GetReflectionBlob();
			const Shader* pUnderlyingShader = pShader->GetShader();

			if (pShader->IsDestroyed())
			{
				LOG("MaterialResource", "Given shader [%d] was destroyed", i);
				return;
			}

			if (pReflectionBlob == nullptr)
			{
				LOG("MaterialResource", "Given shader [%d] was missing reflection blob", i);
				return;
			}

			if (!pShader->IsCompiled())
			{
				LOG("MaterialResource", "Given shader [%d] was invalid/failed to compile", i);
				return;
			}

			if (pUnderlyingShader->GetStage() == ShaderStage::None)
			{
				LOG("MaterialResource", "Given shader [%d] was marked as ShaderStage::None", i);
				return;
			}

			if (shaderStageCounts[(unsigned int)pUnderlyingShader->GetStage()] != 0)
			{
				LOG("MaterialResource", "Duplicate shader found!");
				return;
			}

			/*
			* Increment stage count
			*/
			shaderStageCounts[(unsigned int)pUnderlyingShader->GetStage()]++;
		}

		/*
		* Create new shader state, pipeline resource state and material cpu cache state
		*/
		Array<PipelineResourceTableDesc> newResourceTables;
		for (unsigned int shaderIndex = 0; shaderIndex < mShaders.GetCursor(); shaderIndex++)
		{
			const ShaderResource* pShader = mShaders[shaderIndex];
			const ShaderReflectionBlob* pReflectionBlob = pShader->GetReflectionBlob();
			const Shader* pUnderlyingShader = pShader->GetShader();

			PipelineResourceTableDesc resourceTableDesc = {};
			resourceTableDesc.Stage = pUnderlyingShader->GetStage();
			resourceTableDesc.BufferOffset = 0;
			resourceTableDesc.TextureOffset = 0;
			resourceTableDesc.SamplerOffset = 0;

			/*
			* Collect reflection entries
			*/
			const Array<ShaderReflectionResource> resourceEntries = pReflectionBlob->GetResources();

			
			/*
			* Create stage parameter descriptor
			*/
			MaterialStageParameterDescriptor stageParameterDescriptor = {};

			/*
			* Iterate given reflection blob entries and extract both pipelin resource table descs and material stage&parameter descriptors along the way
			*/
			for (unsigned int entryIndex = 0; entryIndex < resourceEntries.GetCursor(); entryIndex++)
			{
				const ShaderReflectionResource& resourceEntry = resourceEntries[entryIndex];

				MaterialParameterDescriptor parameterDescriptor = {};
				parameterDescriptor.pData = nullptr;
				parameterDescriptor.SizeInBytes = resourceEntry.BufferSize;
				switch (resourceEntry.Type)
				{
				case Portakal::ShaderResourceType::Texture:
				{
					resourceTableDesc.Textures.Add({ resourceEntry.Name });
					parameterDescriptor.Type = MaterialParameterType::Texture;

					break;
				}
				case Portakal::ShaderResourceType::ConstantBuffer:
				{
					resourceTableDesc.Buffers.Add({ resourceEntry.Name });
					parameterDescriptor.Type = MaterialParameterType::Buffer;

					break;
				}
				case Portakal::ShaderResourceType::Sampler:
				{
					resourceTableDesc.Samplers.Add({ resourceEntry.Name});
					parameterDescriptor.Type = MaterialParameterType::Sampler;

					break;
				}
				default:
					break;
				}

				/*
				* Add another parameter to the stage descriptor
				*/
				stageParameterDescriptor.Parameters.Register(resourceEntry.Name,parameterDescriptor);
			}


			/*
			* Register paramater stage descriptor
			*/
			mStageParameterDescriptors.Register(pUnderlyingShader->GetStage(), stageParameterDescriptor);

			mResourceState.Tables.Add(resourceTableDesc);
		}

		/*
		* Set cached registry values for the new registry
		*/
		for (unsigned int stageIndex = 0; stageIndex < cachedStageParameters.GetCursor(); stageIndex++)
		{
			/*
			* Get stage parameter
			*/
			const RegistryEntry<ShaderStage, MaterialStageParameterDescriptor>& stageParameter =  cachedStageParameters[stageIndex];

			/*
			* Try find
			*/
			MaterialStageParameterDescriptor* pFoundStageDescriptor = mStageParameterDescriptors.GetEntryValue(stageParameter.Key);
			if (pFoundStageDescriptor == nullptr)
				continue;

			/*
			* Iterate parameters and find if there is a match
			*/
			for (unsigned int parameterIndex = 0; parameterIndex < stageParameter.Value.Parameters.GetCursor(); parameterIndex++)
			{
				const RegistryEntry<String, MaterialParameterDescriptor>& parameterDescriptor = stageParameter.Value.Parameters[parameterIndex];

				/*
				* Try find this parameter with name and type
				*/
				for (unsigned int i = 0; i < pFoundStageDescriptor->Parameters.GetCursor(); i++)
				{
					RegistryEntry<String,MaterialParameterDescriptor>& descriptor = pFoundStageDescriptor->Parameters[i];
					if (descriptor.Key == parameterDescriptor.Key && descriptor.Value.Type == parameterDescriptor.Value.Type)
					{
						//Set the data ptr
						descriptor.Value.pData = parameterDescriptor.Value.pData;
						break;
					}
				}
			}
		}
	}
	void MaterialResource::InvalidateResourceTables()
	{
		LOG("MaterialResource", "Invalidated resource tables");

		/*
		* Destroy former resource tables
		*/
		DestroyResourceTables();

		/*
		* Material resource will create resource tables per parameter!!!
		* TODO: Maybe should add a way to customize material table layouts????
		*/

		/*
		* Collect table resources
		*/
		for (unsigned int stageIndex = 0; stageIndex < mStageParameterDescriptors.GetCursor(); stageIndex++)
		{
			const RegistryEntry<ShaderStage, MaterialStageParameterDescriptor>& stageDescriptor = mStageParameterDescriptors[stageIndex];

			for (unsigned int parameterIndex = 0; parameterIndex < stageDescriptor.Value.Parameters.GetCursor(); parameterIndex++)
			{
				const RegistryEntry<String, MaterialParameterDescriptor>& parameterDescriptor = stageDescriptor.Value.Parameters[parameterIndex];

				ResourceTableCreateDesc tableCreateDesc = {};

				/*
				* Immediate exit for now
				*/
				if (parameterDescriptor.Value.pData == nullptr)
					return;

				switch (parameterDescriptor.Value.Type)
				{
					case Portakal::MaterialParameterType::Buffer:
					{
						tableCreateDesc.Buffers.Add((GraphicsDeviceObject*)parameterDescriptor.Value.pData);
						break;
					}
					case Portakal::MaterialParameterType::Texture:
					{
						tableCreateDesc.Textures.Add((GraphicsDeviceObject*)((TextureResource*)parameterDescriptor.Value.pData)->GetTexture());
						break;
					}
					case Portakal::MaterialParameterType::Sampler:
					{
						tableCreateDesc.Samplers.Add(((SamplerResource*)parameterDescriptor.Value.pData)->GetSampler());
						break;
					}
					default:
						break;
				}

				/*
				* Create table
				*/
				ResourceTable* pTable = mOwnerDevice->CreateResourceTable(tableCreateDesc);
				mResourceTables.Add(pTable);
			}

			
		}
	}
	void MaterialResource::OnShaderStateChanged(ShaderResource* pShader)
	{
		/*
		* Validate shader
		*/
		if (pShader == nullptr)
		{
			LOG("MaterialResource", "OnShaderCompiled event reported an invalid ShaderResource!. Ignoring the event");
			return;
		}

		/*
		* Re create the material 
		*/
		Create(mShaders);
	}
	void MaterialResource::SignalMaterialStateChanged()
	{
		mStateChangedEvent.Invoke(this);
	}
	void MaterialResource::RemoveFormerShaderSignalEventDelegates()
	{
		/*
		* First remove all the old delegates
		*/
		for (unsigned int i = 0; i < mShaders.GetCursor(); i++)
		{
			ShaderResource* pShader = mShaders[i];

			if (pShader == nullptr)
				return;

			/*
			* Remove former delegates
			*/
			pShader->RemoveOnOnStateChangedEvent(GENERATE_MEMBER_DELEGATE1(this, MaterialResource::OnShaderStateChanged, void, ShaderResource*));
		}
	}
	void MaterialResource::OnTextureStateChanged(TextureResource* pTexture)
	{
		/*
		* Find texture parameter slot
		*/

		/*
		* Update the resource table of that parameter slot
		*/
	}
	void MaterialResource::OnSamplerStateChanged(SamplerResource* pSampler)
	{
		/*
		* Find sampler parameter slot
		*/

		/*
		* Update the resource table of that parameter slot
		*/
	}
	void MaterialResource::DestroyResourceTables()
	{
		/*
		* Destroy current resource tables
		*/
		for (unsigned int i = 0; i < mResourceTables.GetCursor(); i++)
			mResourceTables[i]->Destroy();
		mResourceTables.Clear();
	}
	void MaterialResource::DestroyCore()
	{
		/*
		* Destory command list
		*/
		if (mCmdList != nullptr)
			mCmdList->Destroy();
		mCmdList == nullptr;

		/*
		* Destroy resource table
		*/
		DestroyResourceTables();

		/*
		* Signal that material state has been changed
		*/
		SignalMaterialStateChanged();
	}
}