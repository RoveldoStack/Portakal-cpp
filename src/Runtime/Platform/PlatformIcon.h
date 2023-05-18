#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class Window;

	/// <summary>
	/// Platform agnostic icon operations
	/// </summary>
	class PORTAKAL_API PlatformIcon
	{
	public:
		PlatformIcon() = delete;
		~PlatformIcon() = delete;

		/// <summary>
		/// Loads a icon from path.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="pTargetWindow"></param>
		static void LoadIconFromPath(const String& path,Window* pTargetWindow);
	};
}