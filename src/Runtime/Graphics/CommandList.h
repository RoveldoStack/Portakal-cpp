#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/CommandListCreateDesc.h>
#include <Runtime/Graphics/ViewportDesc.h>
#include <Runtime/Graphics/ScissorDesc.h>
#include <Runtime/Graphics/GraphicsBufferUpdateDesc.h>
#include <Runtime/Graphics/TextureUpdateDesc.h>
#include <Runtime/Graphics/CommandQueueType.h>

namespace Portakal
{
	class Framebuffer;
	class Pipeline;
	class Texture;
	class GraphicsBuffer;

	class GraphicsResourceTable;

	/// <summary>
	/// Records the graphics or compute commands
	/// </summary>
	class PORTAKAL_API CommandList : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE bool IsLocked() const noexcept { return mLock; }
		FORCEINLINE CommandQueueType GetCommandQueueType() const noexcept { return mQueueType; }
		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::CommandList; }

		FORCEINLINE void Lock();
		FORCEINLINE void Unlock();

		FORCEINLINE void BindPipeline(Pipeline* pPipeline);
		FORCEINLINE void BindFramebuffer(Framebuffer* pFramebuffer);

		FORCEINLINE void SetViewports(const Array<ViewportDesc>& viewports);
		FORCEINLINE void SetViewport(const ViewportDesc& viewport);
		FORCEINLINE void SetScissors(const Array<ScissorDesc>& scissors);
		FORCEINLINE void SetScissor(const ScissorDesc& scissor);

		FORCEINLINE void ClearColor(const unsigned int index,const float r, const float g, const float b, const float a);
		FORCEINLINE void ClearDepth(const float depth);
		FORCEINLINE void ClearStencil(const int stencil);

		FORCEINLINE void SetVertexBuffer(GraphicsBuffer* pBuffer);
		FORCEINLINE void SetIndexBuffer(GraphicsBuffer* pBuffer);

		FORCEINLINE void CommitResourceTable(const unsigned int slotIndex, const GraphicsResourceTable* pTable);

		FORCEINLINE void UpdateBuffer(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer);
		FORCEINLINE void UpdateTexture(const TextureUpdateDesc& desc, Texture* pTexture);

		FORCEINLINE void DrawIndexed(const unsigned int indexCount);
	protected:
		CommandList(const CommandListCreateDesc& desc,const CommandQueueType queueType) : mBoundPipeline(nullptr), mBoundFramebuffer(nullptr), mBoundVertexBuffer(nullptr), mBoundIndexBuffer(nullptr),mQueueType(queueType) {}
		virtual ~CommandList() {}

		FORCEINLINE Pipeline* GetBoundPipeline() const noexcept { return mBoundPipeline; }
		FORCEINLINE Framebuffer* GetBoundFramebuffer() const noexcept { return mBoundFramebuffer; }
		FORCEINLINE Array<ViewportDesc> GetBoundViewports() const noexcept { return mBoundViewports; }
		FORCEINLINE Array<ScissorDesc> GetBoundScissors() const noexcept { return mBoundScissors; }
		FORCEINLINE GraphicsBuffer* GetBoundVertexBuffer() const noexcept { return mBoundVertexBuffer; }
		FORCEINLINE GraphicsBuffer* GetBoundIndexBuffer() const noexcept { return mBoundIndexBuffer; }

		FORCEINLINE virtual void LockCore() = 0;
		FORCEINLINE virtual void UnlockCore() = 0;

		FORCEINLINE virtual void BindPipelineCore(Pipeline* pPipeline) = 0;
		FORCEINLINE virtual void BindFramebufferCore(Framebuffer* pFramebuffer) = 0;

		FORCEINLINE virtual void SetViewportsCore(const Array<ViewportDesc>& viewports) = 0;
		FORCEINLINE virtual void SetScissorsCore(const Array<ScissorDesc>& scissors) = 0;

		FORCEINLINE virtual void ClearColorCore(const unsigned int index,const float r, const float g, const float b, const float a) = 0;
		FORCEINLINE virtual void ClearDepthCore(const float depth) = 0;
		FORCEINLINE virtual void ClearStencilCore(const int stencil) = 0;

		FORCEINLINE virtual void SetVertexBufferCore(GraphicsBuffer* pBuffer) = 0;
		FORCEINLINE virtual void SetIndexBufferCore(GraphicsBuffer* pBuffer) = 0;

		FORCEINLINE virtual void CommitResourceTableCore(const unsigned int slotIndex, const GraphicsResourceTable* pTable) = 0;

		FORCEINLINE virtual void DrawIndexedCore(const unsigned int indexCount) = 0;

		FORCEINLINE virtual void UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer) = 0;
		FORCEINLINE virtual void UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture) = 0;

		FORCEINLINE virtual void ClearCachedStateCore() = 0;
	private:
		void CheckBoundFramebuffer();
		void CheckBoundPipeline();
		void CheckBoundVertexIndexBuffer();
		void CheckLock();

		void ClearCachedState();
	private:
		Pipeline* mBoundPipeline;
		Framebuffer* mBoundFramebuffer;
		GraphicsBuffer* mBoundVertexBuffer;
		GraphicsBuffer* mBoundIndexBuffer;
		Array<ViewportDesc> mBoundViewports;
		Array<ScissorDesc> mBoundScissors;
		CommandQueueType mQueueType;
		bool mLock;
	};
}