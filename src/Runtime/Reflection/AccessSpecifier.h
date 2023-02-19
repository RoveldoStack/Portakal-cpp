#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available access specifier flags
	/// </summary>
	enum class PORTAKAL_API AccessSpecifier : unsigned char
	{
		Public = 1,
		Private = 2,
		Protected = 4
	};

	static AccessSpecifier operator |(const AccessSpecifier a, const AccessSpecifier b)
	{
		return (AccessSpecifier)((unsigned char)a | (unsigned char)b);
	}
	static bool operator &(const AccessSpecifier a, const AccessSpecifier b)
	{
		return ((unsigned char)a & (unsigned char)b);
	}
}