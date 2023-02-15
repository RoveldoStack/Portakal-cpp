#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformExplorer
	{
	public:
		PlatformExplorer() = delete;
		~PlatformExplorer() = delete;

		static void OpenExplorer(const String& directoryPath);
	};
}