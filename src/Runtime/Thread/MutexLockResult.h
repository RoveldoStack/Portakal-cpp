#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API MutexLockResult
	{
		Signaled,
		Timeout,
		Invalid
	};
}