#include "CommandBuffer.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/GraphicsResourceTableLayoutDesc.h>
#include <Runtime/Graphics/ResourceStateDesc.h>
#include <Runtime/Graphics/GraphicsDeviceObjects.h>

namespace Portakal
{
	void CommandBuffer::Lock()
	{
		ClearCachedState();

		LockCore();
		_lock = true;
	}
	void CommandBuffer::Unlock()
	{
		UnlockCore();

		_lock = false;
	}
	void CommandBuffer::BindPipeline(Pipeline* pPipeline)
	{
		BindPipelineCore(pPipeline);

		_boundPipeline = pPipeline;
	}
	void CommandBuffer::BindFramebuffer(Framebuffer* pFramebuffer)
	{
		BindFramebufferCore(pFramebuffer);

		_boundFramebuffer = pFramebuffer;
	}
	void CommandBuffer::SetViewports(const Array<ViewportDesc>& viewports)
	{
		CheckBoundFramebuffer();

		SetViewportsCore(viewports);

		_boundViewports = viewports;
	}
	void CommandBuffer::SetViewport(const ViewportDesc& viewport)
	{
		Array<ViewportDesc> viewports = { viewport };

		SetViewports(viewports);
	}
	void CommandBuffer::SetScissors(const Array<ScissorDesc>& scissors)
	{
		CheckBoundFramebuffer();

		SetScissorsCore(scissors);

		_boundScissors = scissors;
	}
	void CommandBuffer::SetScissor(const ScissorDesc& scissor)
	{
		Array<ScissorDesc> scissors = { scissor };

		SetScissors(scissors);
	}
	void CommandBuffer::ClearColor(const float r, const float g, const float b, const float a)
	{
		CheckBoundFramebuffer();

		ClearColorCore(r, g, b, a);
	}
	void CommandBuffer::ClearDepth(const float depth)
	{
		CheckBoundFramebuffer();

		ClearDepthCore(depth);
	}
	void CommandBuffer::ClearStencil(const int stencil)
	{
		CheckBoundFramebuffer();

		ClearStencilCore(stencil);
	}
	void CommandBuffer::SetVertexBuffer(GraphicsBuffer* pBuffer)
	{
		CheckBoundPipeline();

		SetVertexBufferCore(pBuffer);

		_boundVertexBuffer = pBuffer;
	}
	void CommandBuffer::SetIndexBuffer(GraphicsBuffer* pBuffer)
	{
		CheckBoundPipeline();

		SetIndexBufferCore(pBuffer);

		_boundIndexBuffer = pBuffer;
	}
	void CommandBuffer::CommitResourceTable(const unsigned int slotIndex, const GraphicsResourceTable* pTable)
	{
		CheckBoundPipeline();

		/*
		* Validate resource index
		*/
		const ResourceStateDesc& resourceState = GetBoundPipeline()->GetResourceState();

		ASSERT(slotIndex >= 0 && slotIndex < resourceState.Slots.GetCursor(), "CommandBuffer", "Invalid table slot");

		CommitResourceTableCore(slotIndex, pTable);
	}
	void CommandBuffer::UpdateBuffer(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
	{
		UpdateBufferCore(desc, pBuffer);
	}
	void CommandBuffer::UpdateTexture(const TextureUpdateDesc& desc, Texture* pTexture)
	{
		UpdateTextureCore(desc, pTexture);
	}
	void CommandBuffer::DrawIndexed(const unsigned int indexCount)
	{
		CheckBoundVertexIndexBuffer();

		DrawIndexedCore(indexCount);
	}
	void CommandBuffer::CheckBoundFramebuffer()
	{
		ASSERT(_boundFramebuffer != nullptr, "CommandBuffer", "A framebuffer must be bound in order to commit this command");
	}
	void CommandBuffer::CheckBoundPipeline()
	{
		ASSERT(_boundPipeline != nullptr, "CommandBuffer", "A pipeline must be bound in order to commit this command");
	}
	void CommandBuffer::CheckBoundVertexIndexBuffer()
	{
		ASSERT(_boundVertexBuffer != nullptr & _boundIndexBuffer != nullptr, "CommandBuffer", "You must set vertex&index buffer before committing this command");
	}
	void CommandBuffer::CheckLock()
	{
		ASSERT(_lock, "CommandBuffer", "You should lock the command buffer before commiting any commands");
	}
	void CommandBuffer::ClearCachedState()
	{
		ClearCachedStateCore();

		_boundFramebuffer = nullptr;
		_boundPipeline = nullptr;
		_boundVertexBuffer = nullptr;
		_boundIndexBuffer = nullptr;
	}
}