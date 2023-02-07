#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformPaths
	{
	public:
		PlatformPaths() = delete;
		~PlatformPaths() = delete;

		FORCEINLINE static String GetEditorInstallPath();
	};
}