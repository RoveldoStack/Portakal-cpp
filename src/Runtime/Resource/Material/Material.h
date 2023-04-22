#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Containers/Registry.h>
#include <Runtime/Resource/Material/MaterialStageParameterBlock.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/RasterizerStateDesc.h>
#include <Runtime/Graphics/Pipeline/DepthStencil/DepthStencilStateDesc.h>
#include <Runtime/Graphics/Pipeline/Blending/BlendingStateDesc.h>
#include <Runtime/Resource/Shader/ShaderObject.h>
#include <Runtime/Memory/SharedSafeHeap.h>
namespace Portakal
{
	class TextureResource;
	class PORTAKAL_API Material : public ResourceSubObject
	{
		GENERATE_CLASS(Material);
	public:
		Material();
		~Material();

	
		TextureResource* GetTextureParameter(const String& name, const ShaderStage stage) const noexcept;
		RasterizerStateDesc GetRasterizerState() const noexcept { return mRasterizerState; }
		DepthStencilStateDesc GetDepthStencilState() const noexcept { return mDepthStencilState; }
		BlendingStateDesc GetBlendingState() const noexcept { return mBlendingState; }

		void CreateFromShaders(const Array<SharedSafeHeap<ShaderObject>>& shaders);
		void SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture);
		void SetRasterizerState(const RasterizerStateDesc& stateDesc);
		void SetDepthStencilState(const DepthStencilStateDesc& stateDesc);
		void SetBlendingState(const BlendingStateDesc& stateDesc);
	private:
		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	private:
		Registry<ShaderStage, MaterialStageParameterBlock> mParameterBlocks;
		Array<SharedSafeHeap<ShaderObject>> mShaders;
		GraphicsDevice* mOwnerDevice;

		RasterizerStateDesc mRasterizerState;
		DepthStencilStateDesc mDepthStencilState;
		BlendingStateDesc mBlendingState;
	};

#include "Material.reflect.h"
}