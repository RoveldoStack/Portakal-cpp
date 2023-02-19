#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic dialog operations
	/// </summary>
	class PORTAKAL_API PlatformDialog
	{
	public:
		PlatformDialog() = delete;
		~PlatformDialog() = delete;

		/// <summary>
		/// Creates a file dialog
		/// </summary>
		/// <param name="filter"></param>
		static void CreateOpenFileDialog(const String& filter);

		/// <summary>
		/// Creates a folder dialog
		/// </summary>
		/// <returns></returns>
		static String CreateOpenFolderDialog();
	};
}