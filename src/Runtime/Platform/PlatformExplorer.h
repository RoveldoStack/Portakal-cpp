#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic explorer management class
	/// </summary>
	class PORTAKAL_API PlatformExplorer
	{
	public:
		PlatformExplorer() = delete;
		~PlatformExplorer() = delete;

		/// <summary>
		/// Opens a new explorer which targets the directory path
		/// </summary>
		/// <param name="directoryPath"></param>
		static void OpenExplorer(const String& directoryPath);
	};
}