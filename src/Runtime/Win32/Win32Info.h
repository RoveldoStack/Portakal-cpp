#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Win32Info
	{
	public:
		Win32Info() = delete;
		~Win32Info() = delete;

		static unsigned int GetCpuThreadCount();
	};
}