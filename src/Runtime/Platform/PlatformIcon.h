#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class Window;
	class PORTAKAL_API PlatformIcon
	{
	public:
		PlatformIcon() = delete;
		~PlatformIcon() = delete;

		static void LoadIconFromPath(const String& path,Window* pTargetWindow);
	};
}