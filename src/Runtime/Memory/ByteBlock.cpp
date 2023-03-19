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
	ByteBlock::ByteBlock(const ByteBlock& other)
	{
		mBlock = new unsigned char[other.GetBlockSizeInBytes()];
		mSize = other.mSize;
		Memory::Copy(other.mBlock, mBlock, mSize);
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
	void ByteBlock::Copy(void* pData, const unsigned long long size)
	{
		if (mBlock != nullptr)
			delete[] pData;

		mBlock = new unsigned char[size];
		Memory::Copy(pData, mBlock, size);
		mSize = size;
	}
	void ByteBlock::Clear()
	{
		delete[] mBlock;
		mBlock = nullptr;
		mSize = 0;
	}
}