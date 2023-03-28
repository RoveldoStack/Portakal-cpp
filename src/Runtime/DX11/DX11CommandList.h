#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/CommandList.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11CommandList : public CommandList
	{
	public:
		DX11CommandList(const CommandListCreateDesc& desc, DX11Device* pDevice);
		virtual ~DX11CommandList() override;
	private:
		virtual void OnDestroy() override;
		virtual void LockCore() override;
		virtual void UnlockCore() override;
		virtual void BindPipelineCore(Pipeline* pPipeline) override;
		virtual void BindFramebufferCore(Framebuffer* pFramebuffer) override;
		virtual void SetViewportsCore(const Array<ViewportDesc>& viewports) override;
		virtual void SetScissorsCore(const Array<ScissorDesc>& scissors) override;
		virtual void ClearColorCore(const unsigned int index, const ColorRgba& color) override;
		virtual void ClearColorCore(const unsigned int index, const ColorRgbaF& color) override;
		virtual void ClearDepthCore(const float depth) override;
		virtual void ClearStencilCore(const int stencil) override;
		virtual void SetVertexBufferCore(GraphicsBuffer* pBuffer) override;
		virtual void SetIndexBufferCore(GraphicsBuffer* pBuffer) override;
		virtual void CommitResourceTableCore(const unsigned int slotIndex, const GraphicsResourceTable* pTable) override;
		virtual void DrawIndexedCore(const unsigned int indexCount) override;
		virtual void UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer) override;
		virtual void UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture) override;
		virtual void ClearCachedStateCore() override;
	private:
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mContext;
	};
}