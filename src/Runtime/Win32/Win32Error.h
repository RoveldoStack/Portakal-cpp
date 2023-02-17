#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API Win32Error
	{
	public:
		Win32Error() = delete;
		~Win32Error() = delete;

		FORCEINLINE static String GetCurrentError();
	};
}