#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents the available command queue types
	/// </summary>
	enum class PORTAKAL_API CommandQueueType
	{
		Graphics,
		Compute,
		Present,
		Copy
	};
}