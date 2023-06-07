#include "MeshResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Resource/Mesh/MeshUtils.h>
#include <Runtime/Graphics/Buffer/GraphicsBufferUpdateDesc.h>
#include <Runtime/Graphics/Command/CommandList.h>

namespace Portakal
{
	MeshResource::MeshResource(GraphicsDevice* pOwnerDevice)
	{
		mOwnerDevice = pOwnerDevice;
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;

		mCmdList = mOwnerDevice->CreateCommandList({});
	}
	MeshResource::MeshResource()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;

		mCmdList = mOwnerDevice->CreateCommandList({});
	}
	MeshResource::~MeshResource()
	{
		mOwnerDevice = nullptr;
	}
	unsigned long long MeshResource::GetVertexBufferItemCount() const noexcept
	{
		if (mVertexBuffer == nullptr)
			return 0;

		return mVertexBuffer->GetSubItemCount();
	}
	unsigned long long MeshResource::GetVertexBufferItemSize() const noexcept
	{
		if (mVertexBuffer == nullptr)
			return 0;

		return mVertexBuffer->GetSubItemSize();
	}
	unsigned long long MeshResource::GetIndexBufferItemCount() const noexcept
	{
		if (mIndexBuffer == nullptr)
			return 0;

		return mIndexBuffer->GetSubItemCount();
	}
	unsigned long long MeshResource::GetIndexBufferItemSize() const noexcept
	{
		if (mIndexBuffer == nullptr)
			return 0;

		return mIndexBuffer->GetSubItemSize();
	}
	void MeshResource::AllocateVertexes(const unsigned long long subItemSize, const unsigned long long subItemCount, const InputLayoutDesc& inputLayout)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot allocate vertexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate owner device
		*/
		if (mOwnerDevice == nullptr)
			return;

		/*
		* Delete the former vertex buffer
		*/
		DeleteVertexBuffer();

		/*
		* Create vertex buffer
		*/
		GraphicsBufferCreateDesc bufferDesc = {};
		bufferDesc.Type = GraphicsBufferType::VertexBuffer;
		bufferDesc.SubItemCount = subItemCount;
		bufferDesc.SubItemSize = subItemSize;

		mVertexBuffer = mOwnerDevice->CreateBuffer(bufferDesc);

		mVertexSubItemCount = subItemCount;
		mVertexSubItemSize = subItemSize;
		mInputLayout = inputLayout;
	}
	void MeshResource::AllocateVertexes(const unsigned long long subItemSize, const unsigned long long subItemCount)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot allocate vertexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate owner device
		*/
		if (mOwnerDevice == nullptr)
			return;

		if (mInputLayout.Elements.GetCursor() == 0)
		{
			LOG("MeshResource", "Cannot allocate vertexes due to there is no defined input elements yet. You should first use the method override of AllocateVertexes which accepts input element desc array");
			return;
		}

		/*
		* Delete the former vertex buffer
		*/
		DeleteVertexBuffer();

		/*
		* Create vertex buffer
		*/
		GraphicsBufferCreateDesc bufferDesc = {};
		bufferDesc.Type = GraphicsBufferType::VertexBuffer;
		bufferDesc.SubItemCount = subItemCount;
		bufferDesc.SubItemSize = subItemSize;

		mVertexBuffer = mOwnerDevice->CreateBuffer(bufferDesc);

		mVertexSubItemCount = subItemCount;
		mVertexSubItemSize = subItemSize;
	}
	void MeshResource::AllocateIndexes(const MeshIndexType indexType, const unsigned long long subItemCount)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot allocate indexes due to this resource is destroyed");
			return;
		}

		if (mOwnerDevice == nullptr)
			return;

		/*
		* Delete the former index buffer
		*/
		DeleteIndexBuffer();

		/*
		* Create index buffer
		*/
		GraphicsBufferCreateDesc bufferDesc = {};
		bufferDesc.Type = GraphicsBufferType::IndexBuffer;
		bufferDesc.SubItemCount = subItemCount;
		bufferDesc.SubItemSize = MeshUtils::GetMeshIndexTypeSize(indexType);

		mIndexBuffer = mOwnerDevice->CreateBuffer(bufferDesc);

		mIndexSubItemCount = subItemCount;
		mIndexType = indexType;
	}
	void MeshResource::UpdateVertexes(const Byte* pData, const unsigned long long offset, const unsigned long long size)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate device and vertex buffer
		*/
		if (mOwnerDevice == nullptr)
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource does not have a valid owner GraphicsDevice");
			return;
		}
		if (mVertexBuffer == nullptr || mVertexBuffer->IsDestroyed())
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource does not have a valid vertex buffer created with AllocateVertexes before");
			return;
		}
	
		/*
		* Update the buffer
		*/
		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		mCmdList->Lock();
		mCmdList->UpdateBuffer(desc, mVertexBuffer);
		mCmdList->Unlock();
	}
	void MeshResource::UpdateIndexes(const Byte* pData, const unsigned long long offset, const unsigned long long size)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot update indexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate device and vertex buffer
		*/
		if (mOwnerDevice == nullptr)
		{
			LOG("MeshResource", "Cannot update indexes due to this resource does not have a valid owner GraphicsDevice");
			return;
		}
		if (mVertexBuffer == nullptr || mVertexBuffer->IsDestroyed())
		{
			LOG("MeshResource", "Cannot update indexes due to this resource does not have a valid vertex buffer created with AllocateIndexes before");
			return;
		}

		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		/*
		* Update the buffer
		*/
		mCmdList->Lock();
		mCmdList->UpdateBuffer(desc, mIndexBuffer);
		mCmdList->Unlock();
	}
	void MeshResource::UpdateVertexes(const Byte* pData, const unsigned long long offset, const unsigned long long size, CommandList* pTargetCmdList)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate device and vertex buffer
		*/
		if (mOwnerDevice == nullptr)
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource does not have a valid owner GraphicsDevice");
			return;
		}
		if (mVertexBuffer == nullptr || mVertexBuffer->IsDestroyed())
		{
			LOG("MeshResource", "Cannot update vertexes due to this resource does not have a valid vertex buffer created with AllocateVertexes before");
			return;
		}

		/*
		* Update the buffer
		*/
		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		pTargetCmdList->UpdateBuffer(desc, mVertexBuffer);
	}
	void MeshResource::UpdateIndexes(const Byte* pData, const unsigned long long offset, const unsigned long long size, CommandList* pTargetCmdList)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("MeshResource", "Cannot update indexes due to this resource is destroyed");
			return;
		}

		/*
		* Validate device and vertex buffer
		*/
		if (mOwnerDevice == nullptr)
		{
			LOG("MeshResource", "Cannot update indexes due to this resource does not have a valid owner GraphicsDevice");
			return;
		}
		if (mVertexBuffer == nullptr || mVertexBuffer->IsDestroyed())
		{
			LOG("MeshResource", "Cannot update indexes due to this resource does not have a valid vertex buffer created with AllocateIndexes before");
			return;
		}

		/*
		* Update the buffer
		*/
		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		pTargetCmdList->UpdateBuffer(desc, mIndexBuffer);
	}
	void MeshResource::RegisterStateChangedDelegate(const Delegate<void, MeshResource*>& del)
	{
		mStateChangedEvent += del;
	}
	void MeshResource::RemoveStateChangedDelegate(const Delegate<void, MeshResource*>& del)
	{
		mStateChangedEvent -= del;
	}
	void MeshResource::DeleteVertexBuffer()
	{
		if (mVertexBuffer == nullptr || mOwnerDevice == nullptr)
			return;

		mVertexBuffer->Destroy();
		mVertexBuffer = nullptr;

		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
	}
	void MeshResource::DeleteIndexBuffer()
	{
		if (mIndexBuffer == nullptr || mOwnerDevice == nullptr)
			return;

		mIndexBuffer->Destroy();
		mIndexBuffer = nullptr;

		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;
	}
	void MeshResource::SignalStateChangedEvent()
	{
		if (IsDestroyed())
			return;

		mStateChangedEvent.Invoke(this);
	}
	void MeshResource::DestroyCore()
	{
		/*
		* Signal all the listeners
		*/
		SignalStateChangedEvent();

		/*
		* Clear the state changed event invocation list
		*/
		mStateChangedEvent.ClearInvocationList();

		/*
		* Delete the buffers
		*/
		DeleteVertexBuffer();
		DeleteIndexBuffer();

		/*
		* Delete cmd list
		*/
		if(mCmdList == nullptr)
			mCmdList->Destroy();
		mCmdList = nullptr;

		/*
		* Reset the member variables
		*/
		mOwnerDevice = nullptr;
	}
}