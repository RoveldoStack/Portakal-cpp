#pragma once
#include <Runtime/Graphics/CommandBuffer.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12CommandBuffer : public CommandBuffer
	{
	public:
		DX12CommandBuffer(const CommandBufferCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12CommandBuffer() override;

		FORCEINLINE ID3D12CommandList* GetDXCmdList() const noexcept { return _cmdList.Get(); }
	protected:
		virtual void LockCore() override;
		virtual void UnlockCore() override;
		virtual void BindPipelineCore(Pipeline* pPipeline) override;
		virtual void BindFramebufferCore(Framebuffer* pFramebuffer) override;
		virtual void SetViewportsCore(const Array<ViewportDesc>& viewports) override;
		virtual void SetScissorsCore(const Array<ScissorDesc>& scissors) override;
		virtual void ClearColorCore(const float r, const float g, const float b, const float a) override;
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
		Array<DXPTR<ID3D12Resource>> _intermediateUploadBuffers;
		DXPTR<ID3D12GraphicsCommandList> _cmdList;
		ID3D12CommandAllocator* _ownerAllocator;

	};
}