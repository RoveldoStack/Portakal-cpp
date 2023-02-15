#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API Win32Explorer
	{
	public:
		Win32Explorer() = delete;
		~Win32Explorer() = delete;

		static void OpenExplorer(const String& directoryPath);
	};
}