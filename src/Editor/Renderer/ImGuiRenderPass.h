#pragma once
#include <Runtime/Rendering/RenderPass.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Resource/Sampler/SamplerResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>

namespace Portakal
{
	class GraphicsBuffer;
	class PORTAKAL_API ImGuiRenderPass : public RenderPass
	{
	public:
		ImGuiRenderPass();
		~ImGuiRenderPass();
	private:
		// Inherited via RenderPass
		virtual void Execute(CommandList* pCmdList) const override;
		virtual void Initialize() override;
		virtual void Finalize() override;
	private:
		GraphicsBuffer* mConstantBuffer;
		GraphicsDevice* mDevice;
		ShaderResource* mVertexShader;
		ShaderResource* mFragmentShader;
		SamplerResource* mSampler;
		MeshResource* mMesh;
		Pipeline* mPipeline;
		TextureResource* mFontTexture;
		ResourceTable* mBufferResourceTable;
		ResourceTable* mSamplerResourceTable;
		ResourceTable* mFontResourceTable;
	};
}