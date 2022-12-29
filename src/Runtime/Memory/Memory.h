#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Memory utility methods
	/// </summary>
	class PORTAKAL_API Memory
	{
	public:
		Memory() = delete;
		~Memory() = delete;

		static void Copy(const void* pSource, void* pTarget, const unsigned long long size);
		static bool Check(const void* pA, const void* pB, const unsigned long long size);
		static void Set(void* pTarget, unsigned char data, unsigned long long size);
	};
}