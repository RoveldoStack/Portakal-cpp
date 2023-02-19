#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic special path management class
	/// </summary>
	class PORTAKAL_API PlatformPaths
	{
	public:
		PlatformPaths() = delete;
		~PlatformPaths() = delete;

		/// <summary>
		/// Returns the general application load path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String GetApplicationLoadPath();
	};
}