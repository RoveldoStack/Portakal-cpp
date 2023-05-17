#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class Window;
	class PORTAKAL_API Win32Icon
	{
	public:
		Win32Icon() = delete;
		~Win32Icon() = delete;

		static void LoadIconFromPath(const String& path,Window* pTargetWindow);
	};
}