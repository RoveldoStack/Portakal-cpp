#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Containers/Registry.h>
#include <Runtime/Resource/Material/MaterialStageParameterDescriptor.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/RasterizerStateDesc.h>
#include <Runtime/Graphics/Pipeline/DepthStencil/DepthStencilStateDesc.h>
#include <Runtime/Graphics/Pipeline/Blending/BlendingStateDesc.h>
#include <Runtime/Graphics/Pipeline/Resource/ResourceStateDesc.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Memory/SharedSafeHeap.h>
#include <Runtime/Event/Event.h>
namespace Portakal
{
	class TextureResource;
	class SamplerResource;

	PCLASS();
	/// <summary>
	/// Represents an interface for graphics pipeline states with cpu side cached parameters. This is a material ResourceSubObject implementation.
	/// </summary>
	class PORTAKAL_API MaterialResource : public ResourceSubObject
	{
		GENERATE_CLASS(MaterialResource);
	public:
		MaterialResource();
		~MaterialResource();

		/// <summary>
		/// Returns the existing stage resource tables
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Registry<ShaderStage, Array<ResourceTable*>>& GetStageTables() const noexcept { return mStageTables; }

		/// <summary>
		/// Returns a texture parameter with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="stage"></param>
		/// <returns></returns>
		TextureResource* GetTextureParameter(const String& name, const ShaderStage stage) const noexcept;

		/// <summary>
		/// Returns the current shader set of this material
		/// </summary>
		/// <returns></returns>
		const Array<ShaderResource*>& GetShaders() const noexcept { return mShaders; }

		/// <summary>
		/// Returns the rasterizer state of this material
		/// </summary>
		/// <returns></returns>
		const RasterizerStateDesc& GetRasterizerState() const noexcept { return mRasterizerState; }

		/// <summary>
		/// Returns the depth stencil state of this material
		/// </summary>
		/// <returns></returns>
		const DepthStencilStateDesc& GetDepthStencilState() const noexcept { return mDepthStencilState; }

		/// <summary>
		/// Returns the blending state of this material
		/// </summary>
		/// <returns></returns>
		const BlendingStateDesc& GetBlendingState() const noexcept { return mBlendingState; }

		/// <summary>
		/// Returns the resource state of this material
		/// </summary>
		/// <returns></returns>
		const ResourceStateDesc& GetResourceState() const noexcept { return mResourceState; }

		/// <summary>
		/// Creates anew material with the specified shaders and pipeline states
		/// </summary>
		/// <param name="shaders"></param>
		/// <param name="rasterizerDesc"></param>
		/// <param name="depthStencilDesc"></param>
		/// <param name="blendingDesc"></param>
		void Create(const Array<ShaderResource*>& shaders, const RasterizerStateDesc& rasterizerDesc,const DepthStencilStateDesc& depthStencilDesc, const BlendingStateDesc& blendingDesc);

		/// <summary>
		/// Creates anew material with the specified shaders and the existing pipeline states
		/// </summary>
		/// <param name="shaders"></param>
		void Create(const Array<ShaderResource*>& shaders);

		/// <summary>
		/// Sets a texture for the cached cpu side of the material
		/// </summary>
		/// <param name="name"></param>
		/// <param name="stage"></param>
		/// <param name="pTexture"></param>
		void SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture);

		/// <summary>
		/// Sets a sampler for the cached cpu side of the material
		/// </summary>
		/// <param name="name"></param>
		/// <param name="stage"></param>
		/// <param name="pSampler"></param>
		void SetSamplerParameter(const String& name, const ShaderStage stage, SamplerResource* pSampler);

		/// <summary>
		/// Sets a new rasterizer state for the material
		/// </summary>
		/// <param name="stateDesc"></param>
		void SetRasterizerState(const RasterizerStateDesc& stateDesc);

		/// <summary>
		/// Sets a new depth stencil state for the material
		/// </summary>
		/// <param name="stateDesc"></param>
		void SetDepthStencilState(const DepthStencilStateDesc& stateDesc);

		/// <summary>
		/// Sets a new blending state for the material
		/// </summary>
		/// <param name="stateDesc"></param>
		void SetBlendingState(const BlendingStateDesc& stateDesc);

		/// <summary>
		/// Register anew delegate to the state changed event of this material
		/// </summary>
		/// <param name="del"></param>
		void RegisterStateChangedDelegate(const Delegate<void, MaterialResource*>& del);

		/// <summary>
		/// Removes the existing state changed delegate from the event of this material
		/// </summary>
		/// <param name="del"></param>
		void RemoveStateChangedDelegate(const Delegate<void, MaterialResource*>& del);
	private:
		/// <summary>
		/// Called on when a registered shaders compiled
		/// </summary>
		/// <param name="pShader"></param>
		void OnShaderStateChanged(ShaderResource* pShader);

		/// <summary>
		/// Called when the state of the entire material is invalidated
		/// </summary>
		void Invalidate();

		/// <summary>
		/// Called when only the shaders&pipeline states are invalidated
		/// </summary>
		void InvalidateMaterialState();

		/// <summary>
		/// Called when resource table state is invalidated
		/// </summary>
		void InvalidateResourceTables();

		/// <summary>
		/// Signals material state changed event
		/// </summary>
		void SignalMaterialStateChanged();

		/// <summary>
		/// Removes the former registered shader on state changed event delegates
		/// </summary>
		void RemoveFormerShaderSignalEventDelegates();

		/// <summary>
		/// Called upon when a texture state changed within the material resource table
		/// </summary>
		/// <param name="pTexture"></param>
		void OnTextureStateChanged(TextureResource* pTexture);

		/// <summary>
		/// Called when a sampler state changed within the material resource table
		/// </summary>
		/// <param name="pSampler"></param>
		void OnSamplerStateChanged(SamplerResource* pSampler);

		/// <summary>
		/// Destorys the current resource tables
		/// </summary>
		void DestroyResourceTables();

		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	private:
		Event<void, MaterialResource*> mStateChangedEvent;
		Registry<ShaderStage, MaterialStageParameterDescriptor> mStageParameterDescriptors;
		Array<ShaderResource*> mShaders;
		GraphicsDevice* mOwnerDevice;

		//Pipeline state
		RasterizerStateDesc mRasterizerState;
		DepthStencilStateDesc mDepthStencilState;
		BlendingStateDesc mBlendingState;
		ResourceStateDesc mResourceState;
		Registry<ShaderStage, Array<ResourceTable*>> mStageTables;

		CommandList* mCmdList;

		//Default resources
		SamplerResource* mDefaultSampler;
		TextureResource* mDefaultTexture;
		GraphicsBuffer* mDefaultBuffer;
	};

#include "MaterialResource.reflect.h"
}