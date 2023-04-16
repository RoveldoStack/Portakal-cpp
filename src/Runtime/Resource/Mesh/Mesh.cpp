#include "Mesh.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Resource/Mesh/MeshUtils.h>
#include <Runtime/Graphics/GraphicsBufferUpdateDesc.h>
namespace Portakal
{
	Mesh::Mesh(GraphicsDevice* pOwnerDevice)
	{
		mOwnerDevice = pOwnerDevice;
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;
	}
	Mesh::Mesh()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;
	}
	Mesh::~Mesh()
	{
		mOwnerDevice = nullptr;
	}
	void Mesh::AllocateVertexes(const byte* pData, const unsigned long long subItemSize, const unsigned long long subItemCount)
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
	}
	void Mesh::AllocateIndexes(const byte* pData, const MeshIndexType indexType, const unsigned long long subItemCount)
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
	void Mesh::UpdateVertexes(const byte* pData, const unsigned long long offset, const unsigned long long size)
	{
		if (mOwnerDevice == nullptr || mVertexBuffer == nullptr)
			return;

		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		mOwnerDevice->UpdateBuffer(mVertexBuffer, desc);
	}
	void Mesh::UpdateIndexes(const byte* pData, const unsigned long long offset, const unsigned long long size)
	{
		if (mOwnerDevice == nullptr || mIndexBuffer == nullptr)
			return;

		GraphicsBufferUpdateDesc desc = {};
		desc.pData = pData;
		desc.Offset = offset;
		desc.Size = size;

		mOwnerDevice->UpdateBuffer(mIndexBuffer, desc);

	}
	void Mesh::DeleteVertexBuffer()
	{
		if (mVertexBuffer == nullptr || mOwnerDevice == nullptr)
			return;

		mVertexBuffer->Destroy();
		mVertexBuffer = nullptr;

		mVertexSubItemCount = 0;
		mVertexSubItemSize = 0;
	}
	void Mesh::DeleteIndexBuffer()
	{
		if (mIndexBuffer == nullptr || mOwnerDevice == nullptr)
			return;

		mIndexBuffer->Destroy();
		mIndexBuffer = nullptr;

		mIndexSubItemCount = 0;
		mIndexType = MeshIndexType::Unknown;
	}
	void Mesh::DestroyCore()
	{
		DeleteVertexBuffer();
		DeleteIndexBuffer();

		mOwnerDevice = nullptr;
	}
}