#include "ByteBlock.h"
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	ByteBlock::ByteBlock(const void* pData, const unsigned long long sizeInBytes)
	{
		_block = new unsigned char[sizeInBytes];
		Memory::Copy(pData, _block, sizeInBytes);

		_size = sizeInBytes;
	}
	ByteBlock::ByteBlock(const unsigned long long sizeInBytes)
	{
		_block = new unsigned char[sizeInBytes];
		_size = sizeInBytes;
	}
	ByteBlock::ByteBlock()
	{
		_block = nullptr;
		_size = 0;
	}
	ByteBlock::~ByteBlock()
	{
		if (_block != nullptr)
			delete[] _block;
	}
	const unsigned char* ByteBlock::GetBlockDataPtr(const unsigned long long offset) const
	{
		return (_block + offset);
	}
	unsigned long long ByteBlock::GetBlockSizeInBytes() const
	{
		return _size;
	}
}