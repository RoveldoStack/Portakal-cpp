#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Mesh/MeshIndexType.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementDesc.h>
namespace Portakal
{
	PCLASS();
	class PORTAKAL_API MeshResource : public ResourceSubObject
	{
		GENERATE_CLASS(MeshResource);
	public:
		MeshResource(GraphicsDevice* pOwnerDevice);
		MeshResource();
		~MeshResource();

		void AllocateVertexes(const Byte* pData,const unsigned long long subItemSize,const unsigned long long subItemCount,const Array<InputElementDesc>& inputElements);
		void AllocateIndexes(const Byte* pData,const MeshIndexType indexType,const unsigned long long subItemCount);

		void UpdateVertexes(const Byte* pData,const unsigned long long offset,const unsigned long long size);
		void UpdateIndexes(const Byte* pData,const unsigned long long offset,const unsigned long long size);
	private:
		void DeleteVertexBuffer();
		void DeleteIndexBuffer();
		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mOwnerDevice;
		GraphicsBuffer* mVertexBuffer;
		GraphicsBuffer* mIndexBuffer;
		Array<InputElementDesc> mInputElements;
		unsigned long long mVertexSubItemCount;
		unsigned long long mVertexSubItemSize;
		unsigned long long mIndexSubItemCount;
		MeshIndexType mIndexType;
	};

#include "MeshResource.reflect.h"
}