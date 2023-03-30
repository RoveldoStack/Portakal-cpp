#pragma once
#include <Runtime/Graphics/CommandList.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12GraphicsCommandList : public CommandList
	{
	public:
		DX12GraphicsCommandList(const CommandListCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12GraphicsCommandList() override;

		FORCEINLINE ID3D12CommandList* GetDXCmdList() const noexcept { return mCmdList.Get(); }
	protected:
		virtual void LockCore() override;
		virtual void UnlockCore() override;
		virtual void BindPipelineCore(Pipeline* pPipeline) override;
		virtual void BindFramebufferCore(Framebuffer* pFramebuffer) override;
		virtual void SetViewportsCore(const Array<ViewportDesc>& viewports) override;
		virtual void SetScissorsCore(const Array<ScissorDesc>& scissors) override;
		virtual void ClearColorCore(const unsigned int index,const ColorRgba& color) override;
		virtual void ClearColorCore(const unsigned int index, const ColorRgbaF& color) override;
		virtual void ClearDepthCore(const float depth) override;
		virtual void ClearStencilCore(const int stencil) override;
		virtual void SetVertexBufferCore(GraphicsBuffer* pBuffer) override;
		virtual void SetIndexBufferCore(GraphicsBuffer* pBuffer) override;
		virtual void CommitResourceTableCore(const unsigned int slotIndex, const ResourceTable* pTable) override;
		virtual void DrawIndexedCore(const unsigned int indexCount) override;
		virtual void UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer) override;
		virtual void UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture) override;
		virtual void ClearCachedStateCore() override;

	private:
		void FreeFormerFramebufferBarriers();
	private:
		Array<DXPTR<ID3D12Resource>> mIntermediateUploadBuffers;
		DXPTR<ID3D12GraphicsCommandList5> mCmdList;
		ID3D12CommandAllocator* mAllocator;

		// Inherited via CommandList
		virtual void OnDestroy() override;

	};
}