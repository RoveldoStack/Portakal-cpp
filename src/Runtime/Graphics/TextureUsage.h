#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Supported texture usages
	/// </summary>
	enum class PORTAKAL_API TextureUsage : unsigned int
	{
		ReadOnly = 1,
		ReadWrite = 2,
		RenderTarget = 4,
		DepthStencil = 8,
		Cubemap = 16,
		Copy = 32,
	};

	FORCEINLINE static TextureUsage operator |(const TextureUsage a, const TextureUsage b)
	{
		return (TextureUsage)((unsigned int)a | (unsigned int)b);
	}

	FORCEINLINE static bool operator &(const TextureUsage a, const TextureUsage b)
	{
		return ((unsigned int)a & (unsigned int)b);
	}
}