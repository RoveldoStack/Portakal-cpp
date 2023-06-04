#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Mesh/MeshIndexType.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementDesc.h>
#include <Runtime/Event/Event.h>
#include <Runtime/Graphics/Pipeline/Input/InputLayoutDesc.h>

namespace Portakal
{
	PCLASS();
	/// <summary>
	/// Represents a mesh and graphics pipeline input layout interface. This is ResourceSubObject implementation of a simple mesh
	/// </summary>
	class PORTAKAL_API MeshResource : public ResourceSubObject
	{
		GENERATE_CLASS(MeshResource);
	public:
		MeshResource(GraphicsDevice* pOwnerDevice);
		MeshResource();
		~MeshResource();

		FORCEINLINE const InputLayoutDesc& GetInputLayout() const noexcept { return mInputLayout; }
		FORCEINLINE GraphicsBuffer* GetVertexBuffer() const noexcept { return mVertexBuffer; }
		FORCEINLINE GraphicsBuffer* GetIndexBuffer() const noexcept { return mIndexBuffer; }
		FORCEINLINE unsigned long long GetVertexBufferItemCount() const noexcept;
		FORCEINLINE unsigned long long GetVertexBufferItemSize() const noexcept;
		FORCEINLINE unsigned long long GetIndexBufferItemCount() const noexcept;
		FORCEINLINE unsigned long long GetIndexBufferItemSize() const noexcept;

		/// <summary>
		/// Allocates vertexes with the given input elements
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="subItemSize"></param>
		/// <param name="subItemCount"></param>
		/// <param name="inputElements"></param>
		void AllocateVertexes(const unsigned long long subItemSize,const unsigned long long subItemCount,const InputLayoutDesc& inputLayout);

		/// <summary>
		/// Allocates vertexes with the existing input elements
		/// </summary>
		/// <param name="subItemSize"></param>
		/// <param name="subItemCount"></param>
		void AllocateVertexes(const unsigned long long subItemSize, const unsigned long long subItemCount);

		/// <summary>
		/// Allocates indexes
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="indexType"></param>
		/// <param name="subItemCount"></param>
		void AllocateIndexes(const MeshIndexType indexType,const unsigned long long subItemCount);

		/// <summary>
		/// Updates the underlying vertex buffer
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="offset"></param>
		/// <param name="size"></param>
		void UpdateVertexes(const Byte* pData,const unsigned long long offset,const unsigned long long size);

		/// <summary>
		/// Updates the underlying index buffer
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="offset"></param>
		/// <param name="size"></param>
		void UpdateIndexes(const Byte* pData,const unsigned long long offset,const unsigned long long size);

		/// <summary>
		/// Updates the underlying vertex buffer with the given command list
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="offset"></param>
		/// <param name="size"></param>
		void UpdateVertexes(const Byte* pData, const unsigned long long offset, const unsigned long long size,CommandList* pTargetCmdList);

		/// <summary>
		/// Updates the underlying index buffer with the given command list
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="offset"></param>
		/// <param name="size"></param>
		void UpdateIndexes(const Byte* pData, const unsigned long long offset, const unsigned long long size,CommandList* pTargetCmdList);

		/// <summary>
		/// Registers anew delegate for the state changed event of this mesh resource
		/// </summary>
		/// <param name="del"></param>
		void RegisterStateChangedDelegate(const Delegate<void, MeshResource*>& del);

		/// <summary>
		/// Removes the existing delegate for the state changed evnet of this mesh resource
		/// </summary>
		/// <param name="del"></param>
		void RemoveStateChangedDelegate(const Delegate<void, MeshResource*>& del);

	private:
		void DeleteVertexBuffer();
		void DeleteIndexBuffer();
		void SignalStateChangedEvent();

		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	private:
		Event<void, MeshResource*> mStateChangedEvent;
		InputLayoutDesc mInputLayout;
		GraphicsBuffer* mVertexBuffer;
		GraphicsBuffer* mIndexBuffer;
		GraphicsDevice* mOwnerDevice;
		unsigned long long mVertexSubItemCount;
		unsigned long long mVertexSubItemSize;
		unsigned long long mIndexSubItemCount;
		MeshIndexType mIndexType;
		CommandList* mCmdList;
	};

#include "MeshResource.reflect.h"
}