#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents a block of bytes allocated
	/// </summary>
	class PORTAKAL_API ByteBlock
	{
	public:
		ByteBlock(const void* pData, const unsigned long long sizeInBytes);
		ByteBlock(const unsigned long long sizeInBytes);
		ByteBlock(const ByteBlock& other);
		ByteBlock();
		~ByteBlock();

		/// <summary>
		/// Returns the block data ptr with the specified offset
		/// </summary>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE const unsigned char* GetBlockDataPtr(const unsigned long long offset = 0) const;

		/// <summary>
		/// Returns the total block size in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetBlockSizeInBytes() const;

		/*
		* Copies data from another location
		*/
		void Copy(void* pData,const unsigned long long size);

		/*
		* Clears the current data
		*/
		void Clear();

		/// <summary>
		/// Allocates new data block
		/// </summary>
		/// <param name="size"></param>
		void Allocate(const unsigned long long size);

		/// <summary>
		/// Returns the any data interval inside the block
		/// </summary>
		/// <typeparam name="TObject"></typeparam>
		/// <param name="offset"></param>
		/// <returns></returns>
		template<typename TObject>
		FORCEINLINE TObject To(const unsigned long long offset) const
		{
			return *(TObject*)(mBlock + offset);
		}

		FORCEINLINE void operator =(const ByteBlock& other);
		
	private:
		unsigned char* mBlock;
		unsigned long long mSize;
	};
}