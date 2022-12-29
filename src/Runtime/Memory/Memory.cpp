#include "Memory.h"

namespace Portakal
{
	void Memory::Copy(const void* pSource, void* pTarget, const unsigned long long size)
	{
		const unsigned char* pSourceByte = (const unsigned char*)pSource;
		unsigned char* pTargetByte = (unsigned char*)pTarget;

		for (unsigned long i = 0; i < size; i++)
		{
			pTargetByte[i] = pSourceByte[i];
		}
	}
	bool Memory::Check(const void* pA, const void* pB, const unsigned long long size)
	{
		const unsigned char* pAByte = (const unsigned char*)pA;
		const unsigned char* pBByte = (const unsigned char*)pB;

		for (unsigned long long i = 0; i < size; i++)
		{
			if (pAByte[i] != pBByte[i])
				return false;
		}
		return true;
	}
	void Memory::Set(void* pTarget, unsigned char data, unsigned long long size)
	{
		unsigned char* pTargetByte = (unsigned char*)pTarget;

		for (unsigned long long i = 0; i < size; i++)
			pTargetByte[i] = data;
	}
}