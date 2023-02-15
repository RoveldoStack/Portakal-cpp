#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Input/Keys.h>

namespace Portakal
{
	class PORTAKAL_API Win32Keys
	{
	public:
		Win32Keys() = delete;
		~Win32Keys() = delete;

		FORCEINLINE static unsigned int GetKey(const unsigned int vk_key);
	};
}