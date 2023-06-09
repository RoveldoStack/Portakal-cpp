#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Command/CommandListCreateDesc.h>
#include <Runtime/Graphics/ViewportDesc.h>
#include <Runtime/Graphics/ScissorDesc.h>
#include <Runtime/Graphics/Buffer/GraphicsBufferUpdateDesc.h>
#include <Runtime/Graphics/Texture/TextureUpdateDesc.h>
#include <Runtime/Graphics/Command/CommandQueueType.h>
#include <Runtime/Math/Color4.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Graphics/Resource/ResourceSubmitShaderStage.h>

namespace Portakal
{
	class Framebuffer;
	class Pipeline;
	class Texture;
	class GraphicsBuffer;

	class ResourceTable;

	/// <summary>
	/// Represents a command buffer for recording graphics or compute commands for the gpu
	/// </summary>
	class PORTAKAL_API CommandList : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Whether this command list currently recording or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsLocked() const noexcept { return mLock; }

		/// <summary>
		/// Returns which type of queue this command list targets
		/// </summary>
		/// <returns></returns>
		FORCEINLINE CommandQueueType GetCommandQueueType() const noexcept { return mQueueType; }
		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::CommandList; }

		/// <summary>
		/// Locks the command list for recording
		/// </summary>
		FORCEINLINE void Lock();

		/// <summary>
		/// Unlocks the command list from recording and ready for submitting
		/// </summary>
		FORCEINLINE void Unlock();

		/// <summary>
		/// Binds a pipeline state to the pipeline
		/// </summary>
		/// <param name="pPipeline"></param>
		FORCEINLINE void BindPipeline(Pipeline* pPipeline);

		/// <summary>
		/// Binds a framebuffer output to the pipeline
		/// </summary>
		/// <param name="pFramebuffer"></param>
		FORCEINLINE void BindFramebuffer(Framebuffer* pFramebuffer);

		/// <summary>
		/// Sets viewports for the pipeline output
		/// </summary>
		/// <param name="viewports"></param>
		FORCEINLINE void SetViewports(const Array<ViewportDesc>& viewports);

		/// <summary>
		/// Sets a single viewport for the pipeline output
		/// </summary>
		/// <param name="viewport"></param>
		FORCEINLINE void SetViewport(const ViewportDesc& viewport);

		/// <summary>
		/// Sets scissor rects for the pipeline output
		/// </summary>
		/// <param name="scissors"></param>
		FORCEINLINE void SetScissors(const Array<ScissorDesc>& scissors);

		/// <summary>
		/// Sets a single scissor rect for the pipeline output
		/// </summary>
		/// <param name="scissor"></param>
		FORCEINLINE void SetScissor(const ScissorDesc& scissor);

		/// <summary>
		/// Clears the currently bound framebuffer attachment index
		/// </summary>
		/// <param name="index"></param>
		/// <param name="color"></param>
		void ClearColor(const unsigned int index, const Color4& color);

		/// <summary>
		/// Clears the currently bound framebuffer's depth stencil attachment's depth value
		/// </summary>
		/// <param name="depth"></param>
		FORCEINLINE void ClearDepth(const float depth);

		/// <summary>
		/// Clears the currently bound framebuffer's depth stencil attachment's stencil value
		/// </summary>
		/// <param name="stencil"></param>
		FORCEINLINE void ClearStencil(const int stencil);

		/// <summary>
		/// Sets a vertex buffer for the pipeline
		/// </summary>
		/// <param name="pBuffer"></param>
		FORCEINLINE void SetVertexBuffer(GraphicsBuffer* pBuffer);

		/// <summary>
		/// Sets a index buffer for the pipeline
		/// </summary>
		/// <param name="pBuffer"></param>
		FORCEINLINE void SetIndexBuffer(GraphicsBuffer* pBuffer);

		/// <summary>
		/// Commits a resource table for the pipeline.
		/// </summary>
		/// <param name="slotIndex"></param>
		/// <param name="pTable"></param>
		FORCEINLINE void CommitResourceTable(const ResourceSubmitShaderStage stage,const unsigned int slotIndex,const ResourceTable* pTable);

		/// <summary>
		/// Sumbits a buffer update command
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="pBuffer"></param>
		FORCEINLINE void UpdateBuffer(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer);

		/// <summary>
		/// Submits a texture update command
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="pTexture"></param>
		FORCEINLINE void UpdateTexture(const TextureUpdateDesc& desc, Texture* pTexture);

		/// <summary>
		/// Issues an indexed draw call
		/// </summary>
		/// <param name="indexCount"></param>
		FORCEINLINE void DrawIndexed(const unsigned int indexCount,const unsigned int indexStartLocation,const unsigned int vertexStartLocation);

		/// <summary>
		/// Dispatches compute shader
		/// </summary>
		/// <param name="sizeX"></param>
		/// <param name="sizeY"></param>
		/// <param name="sizeZ"></param>
		void Dispatch(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ);
	protected:
		CommandList(const CommandListCreateDesc& desc, const CommandQueueType queueType);
		virtual ~CommandList();

		/// <summary>
		/// Returns the currently bound pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Pipeline* GetBoundPipeline() const noexcept { return mBoundPipeline; }

		/// <summary>
		/// Returns the currently bound framebuffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Framebuffer* GetBoundFramebuffer() const noexcept { return mBoundFramebuffer; }

		/// <summary>
		/// Returns the currently bound viewports
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ViewportDesc> GetBoundViewports() const noexcept { return mBoundViewports; }

		/// <summary>
		/// Returns the currently bound scissors
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ScissorDesc> GetBoundScissors() const noexcept { return mBoundScissors; }

		/// <summary>
		/// Returns the currently bound vertex buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsBuffer* GetBoundVertexBuffer() const noexcept { return mBoundVertexBuffer; }

		/// <summary>
		/// Returns the currently bound index buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsBuffer* GetBoundIndexBuffer() const noexcept { return mBoundIndexBuffer; }

		FORCEINLINE virtual void LockCore() = 0;
		FORCEINLINE virtual void UnlockCore() = 0;

		FORCEINLINE virtual void BindPipelineCore(Pipeline* pPipeline) = 0;
		FORCEINLINE virtual void BindFramebufferCore(Framebuffer* pFramebuffer) = 0;

		FORCEINLINE virtual void SetViewportsCore(const Array<ViewportDesc>& viewports) = 0;
		FORCEINLINE virtual void SetScissorsCore(const Array<ScissorDesc>& scissors) = 0;

		FORCEINLINE virtual void ClearColorCore(const unsigned int index,const Color4& color) = 0;
		FORCEINLINE virtual void ClearDepthCore(const float depth) = 0;
		FORCEINLINE virtual void ClearStencilCore(const int stencil) = 0;

		FORCEINLINE virtual void SetVertexBufferCore(GraphicsBuffer* pBuffer) = 0;
		FORCEINLINE virtual void SetIndexBufferCore(GraphicsBuffer* pBuffer) = 0;

		FORCEINLINE virtual void CommitResourceTableCore(const ResourceSubmitShaderStage stage, const unsigned int slotIndex,const ResourceTable* pTable) = 0;

		FORCEINLINE virtual void DrawIndexedCore(const unsigned int indexCount, const unsigned int indexStartLocation, const unsigned int vertexStartLocation) = 0;
		FORCEINLINE virtual void DispatchCore(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ) = 0;
		FORCEINLINE virtual void UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer) = 0;
		FORCEINLINE virtual void UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture) = 0;

		FORCEINLINE virtual void ClearCachedStateCore() = 0;
	private:
		/// <summary>
		/// Validates bound framebuffer
		/// </summary>
		void CheckBoundFramebuffer();

		/// <summary>
		/// Validates bound pipeline
		/// </summary>
		void CheckBoundPipeline();

		/// <summary>
		/// Validates bound vertex index buffer
		/// </summary>
		void CheckBoundVertexIndexBuffer();

		/// <summary>
		/// Validates lock
		/// </summary>
		void CheckLock();

		/// <summary>
		/// Clears the cached session data
		/// </summary>
		void ClearCachedState();
	private:
		Pipeline* mBoundPipeline;
		Framebuffer* mBoundFramebuffer;
		GraphicsBuffer* mBoundVertexBuffer;
		GraphicsBuffer* mBoundIndexBuffer;
		Array<ViewportDesc> mBoundViewports;
		Array<ScissorDesc> mBoundScissors;
		CommandQueueType mQueueType;
		PlatformCriticalSection* mCriticalSection;
		bool mLock;
	};
}