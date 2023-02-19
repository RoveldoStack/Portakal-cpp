#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API Win32Paths
	{
	public:
		Win32Paths() = delete;
		~Win32Paths() = delete;
		
		FORCEINLINE static String GetApplicationLoadPath();
	};
}