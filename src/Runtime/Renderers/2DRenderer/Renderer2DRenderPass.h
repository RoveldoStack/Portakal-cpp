#pragma once
#include <Runtime/Rendering/RenderPass.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Renderers/2DRenderer/Renderer2DData.h>
#include <Runtime/Resource/Mesh/MeshResource.h>

namespace Portakal
{
	class PORTAKAL_API Renderer2DRenderPass : public RenderPass
	{
	public:
		Renderer2DRenderPass();
		~Renderer2DRenderPass();
	private:
		// Inherited via RenderPass
		virtual void Execute(CommandList* pCmdList) const override;
		virtual void Initialize() override;
		virtual void Finalize() override;
	private:
		MeshResource* mMesh;
		GraphicsBuffer* mConstantBuffer;
		ResourceTable* mConstantBufferTable;

	};
}