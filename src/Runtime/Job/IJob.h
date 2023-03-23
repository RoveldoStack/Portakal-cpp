#pragma once
#include <Runtime/Platform/PlatformThread.h>

namespace Portakal
{
	/// <summary>
	/// Simple executable job on other threads
	/// </summary>
	class PORTAKAL_API IJob
	{
	public:
		IJob() = default;
		virtual ~IJob() = default;

		virtual void Run() = 0;
	};
}