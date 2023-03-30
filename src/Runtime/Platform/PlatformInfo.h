#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API PlatformInfo
	{
	public:
		PlatformInfo() = delete;
		~PlatformInfo() = delete;

		static unsigned int GetCpuThreadCount();
	};
}