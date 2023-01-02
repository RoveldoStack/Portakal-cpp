#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformDialog
	{
	public:
		PlatformDialog() = delete;
		~PlatformDialog() = delete;

		static void CreateOpenFileDialog(const String& filter);
		static String CreateOpenFolderDialog();
	};
}