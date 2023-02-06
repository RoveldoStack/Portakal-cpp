#include "ByteBlock.h"
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	ByteBlock::ByteBlock(const void* pData, const unsigned long long sizeInBytes)
	{
		mBlock = new unsigned char[sizeInBytes];
		Memory::Copy(pData, mBlock, sizeInBytes);

		mSize = sizeInBytes;
	}
	ByteBlock::ByteBlock(const unsigned long long sizeInBytes)
	{
		mBlock = new unsigned char[sizeInBytes];
		mSize = sizeInBytes;
	}
	ByteBlock::ByteBlock()
	{
		mBlock = nullptr;
		mSize = 0;
	}
	ByteBlock::~ByteBlock()
	{
		if (mBlock != nullptr)
			delete[] mBlock;
	}
	const unsigned char* ByteBlock::GetBlockDataPtr(const unsigned long long offset) const
	{
		return (mBlock + offset);
	}
	unsigned long long ByteBlock::GetBlockSizeInBytes() const
	{
		return mSize;
	}
}