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

		/// <summary>
		/// Copies the given source location to the target location with respect to given size
		/// </summary>
		/// <param name="pSource"></param>
		/// <param name="pTarget"></param>
		/// <param name="size"></param>
		static void Copy(const void* pSource, void* pTarget, const unsigned long long size);

		/// <summary>
		/// Checks the given two memeory location if they are the same with respect to given size
		/// </summary>
		/// <param name="pA"></param>
		/// <param name="pB"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		static bool Check(const void* pA, const void* pB, const unsigned long long size);

		/// <summary>
		/// Sets the target memeory interval with the given value with respect to given size
		/// </summary>
		/// <param name="pTarget"></param>
		/// <param name="data"></param>
		/// <param name="size"></param>
		static void Set(void* pTarget, unsigned char data, unsigned long long size);
	};
}