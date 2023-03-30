#include "CommandList.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/PipelineResourceTableDesc.h>
#include <Runtime/Graphics/ResourceStateDesc.h>
#include <Runtime/Graphics/GraphicsDeviceObjects.h>

namespace Portakal
{
	void CommandList::Lock()
	{
		//mCriticalSection->Lock();

		ClearCachedState();

		LockCore();
		mLock = true;
	}
	void CommandList::Unlock()
	{
		UnlockCore();

		mLock = false;

		//mCriticalSection->Release();
	}
	void CommandList::BindPipeline(Pipeline* pPipeline)
	{
		BindPipelineCore(pPipeline);

		mBoundPipeline = pPipeline;
	}
	void CommandList::BindFramebuffer(Framebuffer* pFramebuffer)
	{
		BindFramebufferCore(pFramebuffer);

		mBoundFramebuffer = pFramebuffer;
	}
	void CommandList::SetViewports(const Array<ViewportDesc>& viewports)
	{
		//CheckBoundFramebuffer();

		SetViewportsCore(viewports);

		mBoundViewports = viewports;
	}
	void CommandList::SetViewport(const ViewportDesc& viewport)
	{
		Array<ViewportDesc> viewports = { viewport };

		SetViewports(viewports);
	}
	void CommandList::SetScissors(const Array<ScissorDesc>& scissors)
	{
		//CheckBoundFramebuffer();

		SetScissorsCore(scissors);

		mBoundScissors = scissors;
	}
	void CommandList::SetScissor(const ScissorDesc& scissor)
	{
		Array<ScissorDesc> scissors = { scissor };

		SetScissors(scissors);
	}
	void CommandList::ClearColor(const unsigned int index, const ColorRgba& color)
	{
		//CheckBoundFramebuffer();

		ClearColorCore(index, color);
	}
	void CommandList::ClearColor(const unsigned int index, const ColorRgbaF& color)
	{
		//CheckBoundFramebuffer();

		ClearColorCore(index, color);
	}
	void CommandList::ClearDepth(const float depth)
	{
		//CheckBoundFramebuffer();

		ClearDepthCore(depth);
	}
	void CommandList::ClearStencil(const int stencil)
	{
		//CheckBoundFramebuffer();

		ClearStencilCore(stencil);
	}
	void CommandList::SetVertexBuffer(GraphicsBuffer* pBuffer)
	{
		CheckBoundPipeline();

		SetVertexBufferCore(pBuffer);

		mBoundVertexBuffer = pBuffer;
	}
	void CommandList::SetIndexBuffer(GraphicsBuffer* pBuffer)
	{
		CheckBoundPipeline();

		SetIndexBufferCore(pBuffer);

		mBoundIndexBuffer = pBuffer;
	}
	void CommandList::CommitResourceTable(const unsigned int slotIndex, const ResourceTable* pTable)
	{
		CheckBoundPipeline();

		/*
		* Validate resource index
		*/
		const ResourceStateDesc& resourceState = GetBoundPipeline()->GetResourceState();

		ASSERT(slotIndex >= 0 && slotIndex < resourceState.Slots.GetCursor(), "CommandList", "Invalid table slot");

		CommitResourceTableCore(slotIndex, pTable);
	}
	void CommandList::UpdateBuffer(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
	{
		UpdateBufferCore(desc, pBuffer);
	}
	void CommandList::UpdateTexture(const TextureUpdateDesc& desc, Texture* pTexture)
	{
		UpdateTextureCore(desc, pTexture);
	}
	void CommandList::DrawIndexed(const unsigned int indexCount)
	{
		CheckBoundVertexIndexBuffer();

		DrawIndexedCore(indexCount);
	}
	CommandList::CommandList(const CommandListCreateDesc& desc, const CommandQueueType queueType) : mBoundPipeline(nullptr), mBoundFramebuffer(nullptr), mBoundVertexBuffer(nullptr), mBoundIndexBuffer(nullptr), mQueueType(queueType), mLock(false) 
	{
		mCriticalSection = PlatformCriticalSection::Create();
	}
	CommandList::~CommandList()
	{

	}
	void CommandList::CheckBoundFramebuffer()
	{
		ASSERT(mBoundFramebuffer != nullptr, "CommandList", "A framebuffer must be bound in order to commit this command");
	}
	void CommandList::CheckBoundPipeline()
	{
		ASSERT(mBoundPipeline != nullptr, "CommandList", "A pipeline must be bound in order to commit this command");
	}
	void CommandList::CheckBoundVertexIndexBuffer()
	{
		ASSERT(mBoundVertexBuffer != nullptr & mBoundIndexBuffer != nullptr, "CommandList", "You must set vertex&index buffer before committing this command");
	}
	void CommandList::CheckLock()
	{
		ASSERT(mLock, "CommandList", "You should lock the command buffer before commiting any commands");
	}
	void CommandList::ClearCachedState()
	{
		ClearCachedStateCore();

		mBoundFramebuffer = nullptr;
		mBoundPipeline = nullptr;
		mBoundVertexBuffer = nullptr;
		mBoundIndexBuffer = nullptr;
	}
}