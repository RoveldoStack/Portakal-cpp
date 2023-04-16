#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Mesh/MeshIndexType.h>
#include <Runtime/Graphics/GraphicsBuffer.h>
#include <Runtime/Graphics/GraphicsDevice.h>

namespace Portakal
{
	class PORTAKAL_API Mesh : public ResourceSubObject
	{
		GENERATE_CLASS(Mesh);
	public:
		Mesh(GraphicsDevice* pOwnerDevice);
		Mesh();
		~Mesh();

		void AllocateVertexes(const byte* pData,const unsigned long long subItemSize,const unsigned long long subItemCount);
		void AllocateIndexes(const byte* pData,const MeshIndexType indexType,const unsigned long long subItemCount);

		void UpdateVertexes(const byte* pData,const unsigned long long offset,const unsigned long long size);
		void UpdateIndexes(const byte* pData,const unsigned long long offset,const unsigned long long size);
	private:
		void DeleteVertexBuffer();
		void DeleteIndexBuffer();
		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mOwnerDevice;
		GraphicsBuffer* mVertexBuffer;
		GraphicsBuffer* mIndexBuffer;
		unsigned long long mVertexSubItemCount;
		unsigned long long mVertexSubItemSize;
		unsigned long long mIndexSubItemCount;
		MeshIndexType mIndexType;
	};
}