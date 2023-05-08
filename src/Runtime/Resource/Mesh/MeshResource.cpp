#include "MeshResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Resource/Mesh/MeshUtils.h>
#include <Runtime/Graphics/Buffer/GraphicsBufferUpdateDesc.h>
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
	}
	MeshResource::~MeshResource()
	{
		mOwnerDevice = nullptr;
	}
	void MeshResource::AllocateVertexes(const Byte* pData, const unsigned long long subItemSize, const unsigned long long subItemCount, const Array<InputElementDesc>& inputElements)
	{
		DeleteVertexBuffer();
		if (mOwnerDevice == nullptr)
			return;

		GraphicsBufferCreateDesc bufferDesc = {};
		bufferDesc.Type = GraphicsBufferType::VertexBuffer;
		bufferDesc.SubItemCount = subItemCount;
		bufferDesc.SubItemSize = subItemSize;

		mVertexBuffer = mOwnerDevice->CreateBuffer(bufferDesc);

		mVertexSubItemCount = subItemCount;
		mVertexSubItemSize = subItemSize;
		mInputElements = inputElements;
	}
	void MeshResource::AllocateIndexes(const Byte* pData, const MeshIndexType indexType, const unsigned long long subItemCount)
	{
		DeleteIndexBuffer();
		if (mOwnerDevice == nullptr)
			return;

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
		if (mOwnerDevice == nullptr || mVertexBuffer == nullptr)
			return;

		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		mOwnerDevice->UpdateBuffer(mVertexBuffer, desc);
	}
	void MeshResource::UpdateIndexes(const Byte* pData, const unsigned long long offset, const unsigned long long size)
	{
		if (mOwnerDevice == nullptr || mIndexBuffer == nullptr)
			return;

		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		mOwnerDevice->UpdateBuffer(mIndexBuffer, desc);

	}
	void MeshResource::DeleteVertexBuffer()
	{
		if (mVertexBuffer == nullptr || mOwnerDevice == nullptr)
			return;

		mInputElements.Clear();
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
	void MeshResource::DestroyCore()
	{
		DeleteVertexBuffer();
		DeleteIndexBuffer();

		mOwnerDevice = nullptr;
	}
}